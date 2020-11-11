clear all, close all;

airplane = imread('3096_color.jpg');
bird = imread('42049_color.jpg');

airplanePixelVec = genPixelVec(airplane);
birdPixelVec = genPixelVec(bird);

airplaneNormPixelVec = airplanePixelVec/max(airplanePixelVec,[],'all');
birdNormPixelVec = birdPixelVec/max(birdPixelVec,[],'all');

%load('imageVectors');

%Using 2 Gaussian components to segment the images
[Aalpha,Amu,Asigma] = MLEGMM(airplaneNormPixelVec',1e-2,2);
Asegment = MAP(airplaneNormPixelVec',Aalpha,Amu,Asigma,2);
AirplaneSeIm1 = genSegImg(airplanePixelVec,Asegment,2);
figure(1),subplot(1,2,1), image(airplane),subplot(1,2,2),image(AirplaneSeIm1)

[Balpha,Bmu,Bsigma] = MLEGMM(birdNormPixelVec',5e-2,2);
Bsegment = MAP(birdNormPixelVec',Balpha,Bmu,Bsigma,2);
BirdSeIm1 = genSegImg(birdPixelVec,Bsegment,2);
figure(2),subplot(1,2,1), image(bird),subplot(1,2,2),image(BirdSeIm1)

%Using Cross-Validation to find optimal number of components, train the
%model using test data and segment the image
ANgmm = C_V(airplaneNormPixelVec');
[Aalpha,Amu,Asigma] = MLEGMM(airplaneNormPixelVec',5e-2,ANgmm);
Asegment = MAP(airplaneNormPixelVec',Aalpha,Amu,Asigma,ANgmm);
AirplaneSeIm2 = genSegImg(airplanePixelVec,Asegment,ANgmm);
figure(3),subplot(1,2,1), image(airplane),subplot(1,2,2),image(AirplaneSeIm2)


BNgmm = C_V(birdNormPixelVec');
[Balpha,Bmu,Bsigma] = MLEGMM(birdNormPixelVec',5e-2,BNgmm);
Bsegment = MAP(birdNormPixelVec',Balpha,Bmu,Bsigma,BNgmm);
BirdSeIm2 = genSegImg(birdPixelVec,Bsegment,BNgmm);
figure(4),subplot(1,2,1), image(bird),subplot(1,2,2),image(BirdSeIm2)

%Cross-Validation to find optimal number of gaussian components 
function Ngmm = C_V(x)
    s = round(length(x)/10);
    done = 0;
    t = 0;
    currentScore = -inf;
    while ~done
        t = t+1;
        score = 0; 
        %10-fold
        for k = 1:10
            x_validate = [];
            x_train = [];
            y_validate = [];
            y_train = [];
            if k == 1
                x_validate = x(:,[1:(k*s)]);
                x_train = x(:,[(k*s+1):end]);
            elseif k == 10 
                x_validate = x(:,[(length(x)-s+1):end]);
                x_train = x(:,[1:(length(x)-s)]);
            else 
                x_train = x(:,[1:(((k-1)*s))]);
                x_validate = x(:,[(((k-1)*s)+1):(k*s)]);
                x_train = [x_train x(:,[(k*s+1):end])];                
            end
                
            [Ealpha, Emu, Esigma] = MLEGMM(x_train,1e-1,t);
            score = score + sum(log(sum(evalgmm(x_validate,Emu,Esigma,Ealpha,t))));
        end
        NewScore = sum(score)/10; 
        
        if NewScore < currentScore
            done = 1;
            Ngmm = t-1;
        else 
            currentScore = NewScore;
        end 
    end
end
%generate an image where each color represents the classification of a %pixel
function Simage = genSegImg(pixelVec,segment,M)
    colors = round(rand(M,3)*255);
    for i = 1:length(pixelVec)
        for c = 1:M
            if segment(i) == c
                Simage(pixelVec(i,1), pixelVec(i,2),1) = colors(c,1);
                Simage(pixelVec(i,1), pixelVec(i,2),2) = colors(c,2);
                Simage(pixelVec(i,1), pixelVec(i,2),3) = colors(c,3);
                break;
            end 
        end      
    end
    Simage = uint8(round(Simage));
end
%MAP classification rule to assign each pixel to a cluster
function segment = MAP(x,alpha,mu,sigma,M)

    score = evalgmm(x,mu,sigma,alpha,M);
    
     [~,segment] = max(score);

end 
%generate the raw feature vector of an image 
function pixelVec = genPixelVec(image)
    
    s = size(image);
    pixelVec = [];
    for row = 1:s(1)
        for col = 1:s(2)
            pixel(1) = row;
            pixel(2) = col;
            pixel(3) = image(row,col,1);
            pixel(4) = image(row,col,2);
            pixel(5) = image(row,col,3);
            pixelVec = [pixelVec; pixel];
        end 
    end
end
%ML algorithm to estimate GMM parameters
function [Ealpha, Emu, Esigma] = MLEGMM(x,delta,M)

    converged = 0; d = 5; regWeight = 1e-10; N = length(x);

    Ealpha = ones(1,M)/M;
    shuffledIndices = randperm(N);
    Emu = x(:,shuffledIndices(1:M)); % pick M random samples as initial mean estimates
    [~,assignedCentroidLabels] = min(pdist2(Emu',x'),[],1); % assign each sample to the nearest mean
    for m = 1:M % use sample covariances of initial assignments as initial covariance estimates
        Esigma(:,:,m) = cov(x(:,find(assignedCentroidLabels==m))') + regWeight*eye(d,d);
    end
    t = 0; %displayProgress(t,x,alpha,mu,Sigma);

    while ~converged & t <=300

        for l = 1:M
            temp(l,:) = repmat(Ealpha(l),1,N).*(mvnpdf(x',Emu(:,l)',Esigma(:,:,l)))';
        end

        plgivenx = temp./sum(temp,1);
        alphaNew = mean(plgivenx,2);
        w = plgivenx./repmat(sum(plgivenx,2),1,N);
        muNew = x*w';
        for l = 1:M
            v = x-repmat(muNew(:,l),1,N);
            u = repmat(w(l,:),d,1).*v;
            SigmaNew(:,:,l) = u*v' + regWeight*eye(d,d); % adding a small regularization term
        end
        Dalpha = sum(abs(alphaNew-Ealpha'));
        Dmu = sum(sum(abs(muNew-Emu)));
        DSigma = sum(sum(abs(abs(SigmaNew-Esigma))));
        converged = ((Dalpha+Dmu+DSigma)<delta); % Check if converged
        Ealpha = alphaNew; Emu = muNew; Esigma = SigmaNew;
        t = t+1;  
    end 
end 
%Evaluate the pdf of each of the components in the GMM 
 function pdf = evalgmm(x,mu,sigma,alpha,M)
    
    for i = 1:M % evaluate the GMM on the grid
        pdf(i,:) = (mvnpdf(x',mu(:,i)',sigma(:,:,i)))'*alpha(i);    
    end 
end
