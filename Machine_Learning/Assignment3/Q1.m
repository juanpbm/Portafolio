close all, clear all 

%Generate Datasets 
[x100,label100,sigma,mu,N100] = genData(100);
[x200,label200,~,~,N200] = genData(200);
[x500,label500,~,~,N500] = genData(500);
[x1000,label1000,~,~,N1000] = genData(1000);
[x2000,label2000,~,~,N2000] = genData(2000);
[x5000,label5000,~,~,N5000] = genData(5000);
[x10k,label10k,~,~,N10k] = genData(10000);

%Theoretically Optimal Classifier
TError = MLval(x10k,label10k,mu,sigma,N10k);

%Model Order Selection
Np100 = C_V(x100,label100,N100);
Np200 = C_V(x200,label200,N200);
Np500 = C_V(x500,label500,N500);
Np1000 = C_V(x1000,label1000,N1000);
Np2000 = C_V(x2000,label2000,N2000);
Np5000 = C_V(x5000,label5000,N5000);

%NN Model Training
p100 = NNtrain(x100,label100,Np100,100);
p200 = NNtrain(x200,label200,Np200,200);
p500 = NNtrain(x500,label500,Np500,500);
p1000 = NNtrain(x1000,label1000,Np1000,1000);
p2000 = NNtrain(x2000,label2000,Np2000,2000);
p5000 = NNtrain(x5000,label5000,Np5000,5000);

%Testing Performance Assessment
PE100 = NNtest(p100,x10k,label10k,N10k);
PE200 = NNtest(p200,x10k,label10k,N10k);
PE500 = NNtest(p500,x10k,label10k,N10k);
PE1000 = NNtest(p1000,x10k,label10k,N10k);
PE2000 = NNtest(p2000,x10k,label10k,N10k);
PE5000 = NNtest(p5000,x10k,label10k,N10k);

%Results
TError 
Modelorder = [Np100 Np200 Np500 Np1000 Np2000 Np5000]
PE = [PE100 PE200 PE500 PE1000 PE2000 PE5000]
xaxis = [100 200 500 1000 2000 5000];
%Plot
figure(2), semilogx(xaxis,PE),hold on, semilogx(xaxis,PE,'o'),hold on,
plot(xlim, TError*[1 1]),xlabel('Log of number of samples used to train'),
ylabel('Probability of error'), title('Results');

%Shuffle the Dataset to increase the efficiency of the Cross validation 
function [newx,newlabel] = shuffle(x,label)
    for i = 1:length(x)
       ind(i) = i; 
    end
    ind = randperm(length(ind));
    
    for i = 1:length(x)
       newx(i,:) = x(ind(i),:); 
       newlabel(i,:) = label(ind(i),:);
    end
end 
%Cross Validation function with 10-fold 
function order = C_V(x,label,N)
    s = length(x)/10;
    [x,label] = shuffle(x,label);
    done = 0;
    Np = 0;
    currentScore = 1;
    
    while ~done 
        Np = Np+1;
        orderPE = 0;
        %10-fold
        for k = 1:10
            x_validate = [];
            x_train = [];
            label_validate = [];
            label_train = [];
            if k == 1
               x_validate = x([1:(k*s)],:);
               x_train = x([(k*s+1):end],:);
               label_validate = label([1:(k*s)],:);
               label_train = label([(k*s+1):end],:);
               
            elseif k == 10 
               x_validate = x([(length(x)-s+1):end],:);
               x_train = x([1:(length(x)-s)],:);
               label_validate = label([(length(x)-s+1):end],:);
               label_train = label([1:(length(x)-s)],:);
               
            else 
                x_train = x([1:(((k-1)*s))],:);
                x_validate = x([(((k-1)*s)+1):(k*s)],:);
                x_train = [x_train ; x([(k*s+1):end],:)];                
                label_train = label([1:(((k-1)*s))],:);
                label_validate = label([(((k-1)*s)+1):(k*s)],:);
                label_train = [label_train ; label([(k*s+1):end],:)];
            end
            
            N_validate = sum(label_validate,1);
            p = NNtrain(x_train,label_train,Np,length(x_train));
            orderPE = orderPE + NNtest(p,x_validate,label_validate,N_validate);
        end
        NewScore  = (1/10)*orderPE; 
        if NewScore > currentScore
            done = 1;
        else 
            currentScore = NewScore;
        end 
        Np
    end 
    order = Np-1;
end
% test the NN estimated with a new 10k samples dataset 
function TPE = NNtest(p,x,label,N)
   
    h = L2MLP(x,p);
    
    [~,decision] = max (h',[],2);
    [~,label] = max(label,[],2);
    pi1 = zeros(1,5);pi2 = zeros(1,5);pi3 = zeros(1,5);pi4 = zeros(1,5);
    pi5 = zeros(1,5);
     for i = 1:5
        indi1(i) = length(find(decision==i & label==1)); if N(1) ~= 0 pi1(i) = indi1(i)/N(1);end  
        indi2(i) = length(find(decision==i & label==2)); if N(2) ~= 0 pi2(i) = indi2(i)/N(2);end 
        indi3(i) = length(find(decision==i & label==3)); if N(3) ~= 0 pi3(i) = indi3(i)/N(3);end
        indi4(i) = length(find(decision==i & label==4)); if N(4) ~= 0 pi4(i) = indi4(i)/N(4);end
        indi5(i) = length(find(decision==i & label==5)); if N(5) ~= 0 pi5(i) = indi5(i)/N(5);end
    end 
%Total Probability of error 
    TPE = 1 - (pi1(1)*0.2 + pi2(2)*0.2 + pi3(3)*0.2 + pi4(4)*0.2 + pi5(5)*0.2);
    
end
%Train the NN by estimating its parameters 
function p = NNtrain(x,label,Np,N)
   
    for t = 1:3
        %initialize the parameters randomly
        p.w1 = rand(Np,3); 
        p.b1 = rand(Np,1);
        p.w2 = rand(5,Np);
        p.b2 = rand(5,1);
        vecPinit = [p.w1(:);p.b1(:);p.w2(:);p.b2(:)];
        options = optimset('MaxFunEvals',1e6*length(vecPinit));
        [Ep, val] = fminsearch (@(Ep)(CEL(x,Ep,label,N,Np)),vecPinit,options);

        p.w1 = reshape(Ep(1:3*Np),Np,3);
        p.b1 = Ep((3*Np+1):(3*Np+Np));
        p.w2 = reshape(Ep((4*Np+1):(9*Np)),5,Np);
        p.b2 = Ep((9*Np+1):end);
        scores(t) = val;
        allp(t) = p; 
    end 
    [~,Min] = min(scores);
    
    p = allp(Min);
end 
%2 layer MLP 
function h = L2MLP(D, p)
    %First Layer ISRU activation function
    ISRU = @(z) z./(sqrt(1+z.^2));
    
    x = p.w1*D' + p.b1;
    z = ISRU(x);
    
    v = p.w2*z + p.b2;
    %Soft Max layer 
    for i = 1:size(v,1)
        h(i,:) = (exp(v(i,:)))./(sum(exp(v),1));
    end  
end
%Cross Entropy Calculator 
function entropy = CEL(D, vecp, label,N,Np)
    p.w1 = reshape(vecp(1:3*Np),Np,3);
    p.b1 = repmat(vecp((3*Np+1):(3*Np+Np)),1,N);
    p.w2 = reshape(vecp((4*Np+1):(9*Np)),5,Np);
    p.b2 = repmat(vecp((9*Np+1):end),1,N);
    h = L2MLP(D,p);
    %Cross Entropy Loss Function  
    entropy = (1/N)*sum(sum(-(label.*log(h')))); 
end 
%Theoretical min probability of error using ML (MAP with equal priors)
function  TPE = MLval(x,label,mu,sigma,N)
    score = [];
    for i = 1:5
        xi = mvnpdf(x, mu(:,:,i), sigma(:,:,i));
        score = [score xi];
    end 
    [~,decision] = max(score,[],2);
    [~,label] = max(label,[],2);
    for i = 1:5
        indi1(i) = length(find(decision==i & label==1)); pi1(i) = indi1(i)/N(1); 
        indi2(i) = length(find(decision==i & label==2)); pi2(i) = indi2(i)/N(2); 
        indi3(i) = length(find(decision==i & label==3)); pi3(i) = indi3(i)/N(3); 
        indi4(i) = length(find(decision==i & label==4)); pi4(i) = indi4(i)/N(4); 
        indi5(i) = length(find(decision==i & label==5)); pi5(i) = indi5(i)/N(5); 
    end 
    TPE = 1 - (pi1(1)*0.2 + pi2(2)*0.2 + pi3(3)*0.2 + pi4(4)*0.2 + pi5(5)*0.2);
end 
%Generate Datasets
function [x,label,sigma,mu, Nc] = genData (N)

    mu (:,:,1) = [0 0 0];
    mu (:,:,2) = [3 0 3];
    mu (:,:,3) = [0 2.8 0];
    mu (:,:,4) = [-3 -0 -3];
    mu (:,:,5) = [-0 -2.8 -0];

    sigma(:,:,1) = [2 -.2 .2;-.2 2 -.2;.2 -.2 2];
    sigma(:,:,2) = [2 -0.4 0.3;-0.4 2 -0.4;0.3 -0.4 2];
    sigma(:,:,3) = [2 0.4 0.3;0.4 2 0.4;0.3 0.4 2];
    sigma(:,:,4) = [1 -.5 .5;-.5 1 -.5;.5 -.5 1];
    sigma(:,:,5) = [1 .5 .5;.5 1 .5;.5 .5 1];

    u = rand(1,N);
    Nc(1) = length(find(u <=0.2));
    Nc(2) = length(find((u > 0.2) & (u <=0.4)));
    Nc(3) = length(find((u > 0.4) & (u <=0.6)));
    Nc(4) = length(find((u > 0.6) & (u <= 0.8)));
    Nc(5) = length(find((u > 0.8)));
    x = [];
    label = [];
    clf;
    for i = 1:5
        
        xi = mvnrnd(mu(:,:,i), sigma(:,:,i), Nc(i));
        labeli = zeros(5,Nc(i));
        labeli(i,:) = 1;
        x = [x; xi];
        label = [label ; labeli'];
        figure(1), plot3(xi(:,1),xi(:,2),xi(:,3),'.'); axis equal,hold on;
        title ('Data'),xlabel('X1'),ylabel('X2'),zlabel('X3');
    end 
end
