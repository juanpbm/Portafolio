close all, clear all

count2k = zeros(1,10); count20k = zeros(1,10); count200k = zeros(1,10);

for i = 1:150
    D2k = (GenDataQ2(2000,1))'; 
    D20k = (GenDataQ2(20000,2))'; 
    D200k = (GenDataQ2(200000,3))';
    
    decision2k = BIC(D2k,2000);
    count2k(decision2k) =  count2k(decision2k) + 1;
    i
    decision20k = BIC(D20k,20000);
    count20k(decision20k) =  count20k(decision20k) + 1;
    i
    decision200k = BIC(D200k,200000);
    count200k(decision200k) =  count200k(decision200k) + 1; 
    i
end 
plotData(D2k',1,1); plotData(D20k',2,1); plotData(D200k',3,1);

figure (2), histogram('BinEdges',[0.5:10.5],'BinCounts',count2k), title('model order selections for 2k samples over 100 experiments,')
figure (3), histogram('BinEdges',[0.5:10.5],'BinCounts',count20k), title('model order selections for 20k samples over 100 experiments,')
figure (4), histogram('BinEdges',[0.5:10.5],'BinCounts',count200k), title('model order selections for 200k samples over 100 experiments,')

plotData(D2k',1,5); plotData(D20k',2,5); plotData(D200k',3,5);
figure(5), clear sgtitle, sgtitle('Plots of Equilevel Contours Overlaid on Data for some Trained-and-Selected Models')

[~,Max] = max(count2k)
[Ealpha2k, Emu2k, Esigma2k] = MLEGMM(D2k,1e-1,Max);
cont(Emu2k,Esigma2k,Ealpha2k,1,5);
[~,Max] = max(count20k)
[Ealpha20k, Emu20k, Esigma20k] = MLEGMM(D20k,1e-1,Max);
cont(Emu20k,Esigma20k,Ealpha20k,2,5);
[~,Max] = max(count200k)
[Ealpha200k, Emu200k, Esigma200k] = MLEGMM(D200k,1e-1,Max);
cont(Emu200k,Esigma200k,Ealpha200k,3,5);

plotData(D2k',1,6); plotData(D20k',2,6); plotData(D200k',3,6);
figure(6), clear sgtitle, sgtitle('Plots of Equilevel Contours Overlaid on Data for some Trained-but-Rejected Models')
[~,Min] = min(count2k)
[Ealpha2k, Emu2k, Esigma2k] = MLEGMM(D2k,1e-1,Min);
cont(Emu2k,Esigma2k,Ealpha2k,1,6);
[~,Min] = min(count20k)
[Ealpha20k, Emu20k, Esigma20k] = MLEGMM(D20k,1e-1,Min);
cont(Emu20k,Esigma20k,Ealpha20k,2,6);
[~,Min] = min(count200k)
[Ealpha200k, Emu200k, Esigma200k] = MLEGMM(D200k,1e-1,Min);
cont(Emu200k,Esigma200k,Ealpha200k,3,6);

function decision = BIC(x,N)
    for i = 1:10
        [Ealpha, Emu, Esigma] = MLEGMM(x,8e-1,i);
        BIC(:,i) = -2*sum(log(evalgmm(x,Emu,Esigma,Ealpha,i)))+(6*i-1)*log(2*N);
    end 
    %figure(2), plot(BIC)
    [~,decision] = min(BIC);
end

function [Ealpha, Emu, Esigma] = MLEGMM(x,delta,M)

    converged = 0; d = 2; regWeight = 1e-10; N = length(x);

    Ealpha = ones(1,M)/M;
    shuffledIndices = randperm(N);
    Emu = x(:,shuffledIndices(1:M)); % pick M random samples as initial mean estimates
    [~,assignedCentroidLabels] = min(pdist2(Emu',x'),[],1); % assign each sample to the nearest mean
    for m = 1:M % use sample covariances of initial assignments as initial covariance estimates
        Esigma(:,:,m) = cov(x(:,find(assignedCentroidLabels==m))') + regWeight*eye(d,d);
    end
    t = 0; %displayProgress(t,x,alpha,mu,Sigma);

    while (~converged) & (t <= 300)

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
        %displayProgress(t,x,Ealpha,Emu,Esigma,M);
    end 
end 

function plotData(x0,i,i2)
figure(i2),sgtitle('Training Data 2k 20k 200k samples');
figure(i2),subplot(2,2,i), plot(x0(:,1),x0(:,2),'.b'); axis equal, hold on;
xlabel('x1'),ylabel('x2');
end 
function cont(mu,sigma,alpha,i,i2)
figure(i2),subplot(2,2,i),
px0 = gmdistribution(mu',sigma,alpha);

Nx = 101; Ny = 99;
xGrid = linspace(-3,7,Nx); yGrid = linspace(-3,7,Ny);
[h,v] = meshgrid(xGrid,yGrid);
gridPoints = [h(:),v(:)];

pdfGMM = pdf(px0,gridPoints);
zGrid = reshape(pdfGMM,Ny,Nx);
% Display the MAP objective contours
minV = min(pdfGMM); maxV = max(pdfGMM);
values = minV + (sqrt(maxV-minV)*linspace(0.1,0.9,21)).^2;
contour(xGrid,yGrid,zGrid,values); xlabel('x_1'), ylabel('x_2'),
%contour(xGrid,yGrid,zGrid); xlabel('x_1'), ylabel('x_2'),
grid on, axis equal,

end 

function x = GenDataQ2(N,i)

alpha = [0.4 0.3 0.2 0.1];
mu(:,:,1) = [3 0];
mu(:,:,2) = [0 3];
mu(:,:,3) = [2 2];
mu(:,:,4) = [1 1];
Sigma(:,:,1) = [2 0;0 1];
Sigma(:,:,2) = [1 0;0 2];
Sigma(:,:,3) = eye(2);
Sigma(:,:,4) = eye(2);

x = (randGMM(N,alpha,mu,Sigma))';
end
function x = randGMM(N,alpha,mu,Sigma)
d = size(mu,2); % dimensionality of samples
cum_alpha = [0,cumsum(alpha)];
u = rand(1,N); x = zeros(d,N); labels = zeros(1,N);
for m = 1:length(alpha)
    ind = find(cum_alpha(m)<u & u<=cum_alpha(m+1)); 
    x(:,ind) = (mvnrnd(mu(:,:,m)', Sigma(:,:,m), length(ind)))';
end
end 
function pdf = evalgmm(x,mu,sigma,alpha,M)
    pdf = zeros(1,size(x,2));
    for i = 1:M % evaluate the GMM on the grid
        pdf = pdf + (mvnpdf(x',mu(:,i)',sigma(:,:,i)))'*alpha(i);    
    end 
end
