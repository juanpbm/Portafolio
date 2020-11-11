close all, clear all

p1 = 0.65; p2 = 0.35;
alpha = [0.5 0.5];
mu1 = [3 0; 0 3];
sigma1(:,:,1) = [2 0;0 1];
sigma1(:,:,2) = [1 0;0 2];
mu2 = [2;2]; sigma2 = eye(2);

[D50,label50,Nc50] = GenDataQ1(50,1); 
[D500,label500,Nc500] = GenDataQ1(500,2); 
[D5k,label5k,Nc5k] = GenDataQ1(5000,3);
[D10k,label10k,Nc10k] = GenDataQ1(10000,4);

%Part 1 MAP
disp("Part 1");
Validate(p1,p2,alpha,mu1,sigma1,mu2,sigma2,D10k,label10k,Nc10k,2); 

%PArt 2.a
disp('part B.a');
x1 = (D5k(find(label5k == 1),:))';
x2 = (D5k(find(label5k == 2),:))';
[Ealpha1, Emu1, Esigma1] = MLEGMM(x1,3e-2);
[Emu2,Esigma2] = GMLE(x2);
Ealpha1 = Ealpha1';
Validate(p1,p2,Ealpha1,Emu1,Esigma1,Emu2,Esigma2,D10k,label10k,Nc10k,4);

%Part 2.b
disp('part B.b');
x1 = (D500(find(label500 == 1),:))';
x2 = (D500(find(label500 == 2),:))';
[Ealpha1, Emu1, Esigma1] = MLEGMM(x1,7.5e-2);
[Emu2,Esigma2] = GMLE(x2);
Ealpha1 = Ealpha1';
Validate(p1,p2,Ealpha1,Emu1,Esigma1,Emu2,Esigma2,D10k,label10k,Nc10k,5);

%Part 2.c

disp('part B.c');
x1 = (D50(find(label50 == 1),:))';
x2 = (D50(find(label50 == 2),:))';
[Ealpha1, Emu1, Esigma1] = MLEGMM(x1,4e-1);
[Emu2,Esigma2] = GMLE(x2);
Ealpha1 = Ealpha1';
Validate(p1,p2,Ealpha1,Emu1,Esigma1,Emu2,Esigma2,D10k,label10k,Nc10k,6);

%Part 3.a
%logistic linear function 
%training set of 50 samples
disp('50 samples');
LLmodel(D50,50,label50,D10k,label10k,Nc10k);
%training set of 500 samples
disp('500 samples');
LLmodel(D500,500,label500,D10k,label10k,Nc10k);
%training set of 5k samples
disp('5k samples');
LLmodel(D5k,5000,label5k,D10k,label10k,Nc10k);

%Part 3.b
%logistic quadratic function
disp('Logistic-quadratic-function-based');
%training set of 50 samples
disp('50 samples');
LQmodel(D50,50,label50,D10k,label10k,Nc10k);
%training set of 500 samples
disp('500 samples');
LQmodel(D500,500,label500,D10k,label10k,Nc10k);
%training set of 5k samples
disp('5k samples');
LQmodel(D5k,5000,label5k,D10k,label10k,Nc10k);

%function to implement the logistic linear aproximation 
function LLmodel(x_train,N_train,label_train,D10k,label10k,Nc10k)
    
    %initialize the parameter, make the b(x) vector, define the function
    %and optimize it
    bx = [ones(1,N_train); x_train(:,1)'; x_train(:,2)'];
    w0 = zeros(3,1); 
    MinF = @(w)(-1/N_train)*sum((label_train-1).*log(1./(1+exp(-w'*bx)))+             (1-(label_train-1)).*log(1-(1./(1+exp(-w'*bx)))));
    options = optimset('MaxFunEvals', 1e5*6);
    w = fminsearch(MinF,w0,options);

    %validation using the 10k sample data  
    bx10k = [ones(1,10000); D10k(:,1)'; D10k(:,2)'];
    H = 1./(1+exp(-w'*bx10k));
    scores = [1-H; H];
    [~,decision] = max(scores,[],1);
    
    %find min probability of error 
    ind11 = find(decision==1 & label10k==1); p11 = length(ind11)/Nc10k(1);     % probability of true negative
    ind21 = find(decision==2 & label10k==1); p21 = length(ind21)/Nc10k(1); % probability of false positive
    ind12 = find(decision==1 & label10k==2); p12 = length(ind12)/Nc10k(2); % probability of false negative
    ind22 = find(decision==2 & label10k==2); p22 = length(ind22)/Nc10k(2); % probability of true positive
    TotalPError = p21*0.65+p12*0.35;
    disp(strcat('min-P error = ',num2str(TotalPError)));
end 

%function to implement the logistic linear aproximation 
function LQmodel(x_train,N_train,label_train,D10k,label10k,Nc10k)

    %initialize the parameter, make the b(x) vector, define the function
    %and optimize it
    bx = [ones(1,N_train); x_train(:,1)'; x_train(:,2)';(x_train(:,1)').^2;(x_train(:,1)').*(x_train(:,2)');(x_train(:,2)').^2];
    w0 = zeros(6,1);
    MinF = @(w)(-1/N_train)*sum((label_train-1).*log(1./(1+exp(-w'*bx)))+(1-(label_train-1)).*log(1-(1./(1+exp(-w'*bx)))));
    options = optimset('MaxFunEvals', 1e5*6);
    w = fminsearch(MinF,w0,options);

    %validation using the 10k sample data 
    bx10k = [ones(1,10000); D10k(:,1)'; D10k(:,2)';(D10k(:,1)').^2;D10k(:,1)'.*D10k(:,2)';(D10k(:,2)').^2];
    H = 1./(1+exp(-w'*bx10k));
    scores = [1-H; H];
    [~,decision] = max(scores,[],1);

    %find min probability of error 
    ind11 = find(decision==1 & label10k==1); p11 = length(ind11)/Nc10k(1); % probability of true negative
    ind21 = find(decision==2 & label10k==1); p21 = length(ind21)/Nc10k(1); % probability of false positive
    ind12 = find(decision==1 & label10k==2); p12 = length(ind12)/Nc10k(2); % probability of false negative
    ind22 = find(decision==2 & label10k==2); p22 = length(ind22)/Nc10k(2); % probability of true positive
    TotalPError1 = p21*0.65+p12*0.35;
    disp(strcat('min-P error = ',num2str(TotalPError1)));
end 
%function of ML algorithm (taken from EMforGMM.m)
function [Ealpha1, Emu1, Esigma1] = MLEGMM(x1,delta)

    converged = 0; M = 2; d = 2; regWeight = 1e-10; N = length(x1);

    Ealpha1 = ones(1,M)/M;
    shuffledIndices = randperm(N);
    Emu1 = x1(:,shuffledIndices(1:M)); % pick M random samples as initial mean estimates
    [~,assignedCentroidLabels] = min(pdist2(Emu1',x1'),[],1); % assign each sample to the nearest mean
    for m = 1:M % use sample covariances of initial assignments as initial covariance estimates
        Esigma1(:,:,m) = cov(x1(:,find(assignedCentroidLabels==m))') + regWeight*eye(d,d);
    end
    t = 0; %displayProgress(t,x,alpha,mu,Sigma);

    while ~converged & t <=500

        for l = 1:M
            temp(l,:) = repmat(Ealpha1(l),1,N).*(mvnpdf(x1',Emu1(:,l)',Esigma1(:,:,l)))';
        end

        plgivenx = temp./sum(temp,1);
        alphaNew = mean(plgivenx,2);
        w = plgivenx./repmat(sum(plgivenx,2),1,N);
        muNew = x1*w';
        for l = 1:M
            v = x1-repmat(muNew(:,l),1,N);
            u = repmat(w(l,:),d,1).*v;
            SigmaNew(:,:,l) = u*v' + regWeight*eye(d,d); % adding a small regularization term
        end
        Dalpha = sum(abs(alphaNew-Ealpha1'));
        Dmu = sum(sum(abs(muNew-Emu1)));
        DSigma = sum(sum(abs(abs(SigmaNew-Esigma1))));
        converged = ((Dalpha+Dmu+DSigma)<delta); % Check if converged
        Ealpha1 = alphaNew; Emu1 = muNew; Esigma1 = SigmaNew;
        t = t+1;  
    end 
end 
% function with sample average and covariance estimator 
function [Emu2,Esigma2] = GMLE(x2)
    N = length(x2);
    Emu2 = mean(x2,2);
    Esigma2 = cov(x2');
end

%function to validate using the 10k sample data set and the MAP desicion rule 
function Validate(p1,p2,alpha,mu1,sigma1,mu2,sigma2, D10k,label10k,Nc10k,i)
score1 = (mvnpdf(D10k,mu1(:,1)',sigma1(:,:,1))*alpha(1) + mvnpdf(D10k,mu1(:,2)',sigma1(:,:,2))*alpha(2))*p1;
score2 = mvnpdf(D10k,mu2',sigma2)*p2;
Scores = [score1 score2];

[~,decision] = max((log(Scores))');

ind11 = find(decision==1 & label10k==1); p11 = length(ind11)/Nc10k(1); % probability of true negative
ind21 = find(decision==2 & label10k==1); p21 = length(ind21)/Nc10k(1); % probability of false positive
ind12 = find(decision==1 & label10k==2); p12 = length(ind12)/Nc10k(2); % probability of false negative
ind22 = find(decision==2 & label10k==2); p22 = length(ind22)/Nc10k(2); % probability of true positive

%MAP ROC Curve
discriminantScore = (log(score1./score2))';
[ROC,tau] = estimateROC(discriminantScore,label10k,Nc10k);
probError = [((ROC(1,:).*p1)+(ROC(3,:).*p2))]; % probability of total error for different threshold values
[pEmin,ind] = min(probError);
plotROC(ROC,ind,i)

TotalPError1 = p21*p1+p12*p2;
disp(strcat('Theoretical min-P error = ',num2str(TotalPError1)));
disp(strcat('ROC min-P error = ',num2str(pEmin)));
end

%ROC estimation nd plottin function (taken from Exam1_Q1.m summe1 2019)
function [ROC,tau] = estimateROC(discriminantScore,label,Nc)
% Generate ROC curve samples
sortedScore = sort(discriminantScore,'ascend');
tau = [sortedScore(1),(sortedScore(2:end)+sortedScore(1:end-1))/2,sortedScore(end)+1];
%thresholds at midpoints of consecutive scores in sorted list
for k = 1:length(tau)
    decision = (discriminantScore <= tau(k))+1;
    ind21 = find(decision==2 & label==1); p21 = length(ind21)/Nc(1); % probability of false positive
    ind22 = find(decision==2 & label==2); p22 = length(ind22)/Nc(2); % probability of true positive
    ind12 = find(decision==1 & label==2); p12 = length(ind12)/Nc(2); % probability of false negative
    ROC(:,k) = [p21;p22;p12];
end
end
 
function plotROC(ROC,ind,i)
% Display the estimated ROC curve with blue o
% and indicate the  min-P(error) classifier with a red +
figure(i), plot(ROC(1,:),ROC(2,:),'bo'); hold on,
plot(ROC(1,ind),ROC(2,ind),'r+'); 
axis equal, xlim([0,1]); ylim([0,1]), xlabel('P False Positive'),ylabel('P True Positive');
title('ROC Curve');
end

%functions to generate and plot the data sets
function [x,label,Nc] = GenDataQ1(N,i)
p1 = 0.65; p2 = 0.35;
alpha = [0.5 0.5];
mu1 = [3 0; 0 3];
sigma1(:,:,1) = [2 0;0 1];
sigma1(:,:,2) = [1 0;0 2];
mu2 = [2;2]; sigma2 = eye(2);

u = rand(1,N)>= p1; N1 = length(find(u==0)); N2 = length(find(u==1)); Nc = [N1 N2];
x0 = (randGMM(N1,alpha,mu1,sigma1))';
x1 = mvnrnd(mu2, sigma2, N2);
x = [x0 ; x1];
label = [ones(1,N1) 2*ones(1,N2)];
plotData(x0,x1,i);
end 

function x = randGMM(N,alpha,mu,Sigma)
d = size(mu,1); % dimensionality of samples
cum_alpha = [0,cumsum(alpha)];
u = rand(1,N); x = zeros(d,N); labels = zeros(1,N);
for m = 1:length(alpha)
    ind = find(cum_alpha(m)<u & u<=cum_alpha(m+1)); 
    x(:,ind) = (mvnrnd(mu(:,m), Sigma(:,:,m), length(ind)))';
end
end
 
function plotData(x0,x1,i)
figure(1),sgtitle('Training Data 50 500 5k 10k samples');
figure(1),subplot(2,2,i), plot(x0(:,1),x0(:,2),'.b'); axis equal, hold on;
figure(1),subplot(2,2,i), plot(x1(:,1),x1(:,2),'.r'); axis equal,hold on;
xlabel('x1'),ylabel('x2');
end 
