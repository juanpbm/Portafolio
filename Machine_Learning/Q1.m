clear all, close all,
%generate 10000 samples from the gaussian pdfs
N = 10000; p0 = 0.65; p1 = 0.35;
u = rand(1,N)>=p0; N0 = length(find(u==0)); N1 = length(find(u==1)); Nc = [N0 N1];
mu0 = [-1/2;-1/2;-1/2]; Sigma0 = [1,-0.5,0.3;-0.5,1,-0.5;0.3,-0.5,1];
x0 = mvnrnd(mu0, Sigma0, N0);
figure(1),subplot(1,2,1), plot3(x0(:,1),x0(:,2),x0(:,3),'.b'); axis equal, hold on;
mu1 = [1;1;1]; Sigma1 = [1,0.3,-0.2;0.3,1,0.3;-0.2,0.3,1];
x1 = mvnrnd(mu1, Sigma1, N1);
figure(1),subplot(1,2,1), plot3(x1(:,1),x1(:,2),x1(:,3),'.r'); axis equal,hold on;
title ('Data');

%put all samples together and make the labels vector
x = [x0 ; x1];
label = [zeros(1,N0) ones(1,N1)];
loss = [0 1; 1 0];

%Part A
%generate the discriminant scores for all samples 
R0 = mvnpdf(x,mu0',Sigma0);
R1 = mvnpdf(x,mu1',Sigma1);
discriminantScore = (log((R0./R1)))';

%PART A.1 
%threshold as a function of priors and loss value
Tgamma = log(((loss(1,2)-loss(2,2))*p1)/((loss(2,1)-loss(1,1))*p0));

%decision and calculation of probabilities of the 4 cases 
decision = (discriminantScore <= Tgamma); % use smallest min-error threshold
ind00 = find(decision==0 & label==0); p100 = length(ind00)/Nc(1); % probability of true negative
ind10 = find(decision==1 & label==0); p110 = length(ind10)/Nc(1); % probability of false positive
ind01 = find(decision==0 & label==1); p101 = length(ind01)/Nc(2); % probability of false negative
ind11 = find(decision==1 & label==1); p111 = length(ind11)/Nc(2); % probability of true positive

%A.2
%estimate the ROC curve and find the value of tao that minimizes the probability of total error 
[ROC,tau] = estimateROC(discriminantScore,Nc,label);
probError = [((ROC(1,:)'*p0)+(ROC(3,:)'*p1))]; % probability of total error for different threshold values
[pEmin,ind] = min(probError);


% Display the estimated ROC curve with blue o
% and indicate the minimizer tau with a red +
figure(1),subplot(1,2,2), plot(ROC(1,:),ROC(2,:),'bo'); hold on,
plot(ROC(1,ind),ROC(2,ind),'r+'); 
axis equal, xlim([0,1]); ylim([0,1]),xlabel('P False Positive'),ylabel('P True Positive');
title('ROC Curve Part A');

%A.3

TotalPError1 = p110*p0+p101*p1;
disp(strcat('P Detect = ',num2str(1-TotalPError1))),  
disp(strcat('P error = ',num2str(TotalPError1))),
disp(strcat('theo gamma = ',num2str(Tgamma)));


disp(strcat('P Detection2 = ',num2str(1-pEmin))),
disp(strcat('P error2 = ',num2str(pEmin))),
disp(strcat('Gamma = ',num2str((tau(ind))))); 


%part B

disp("Part B");
figure(2),subplot(1,2,1), plot3(x0(:,1),x0(:,2),x0(:,3),'.b'); axis equal, hold on;
figure(2),subplot(1,2,1), plot3(x1(:,1),x1(:,2),x1(:,3),'.r'); axis equal,hold on;
title ('Data');
newSigma0 = eye(3);
newSigma1 = eye(3);
%generate the discriminant scores for all samples 
R0 = mvnpdf(x,mu0',newSigma0);
R1 = mvnpdf(x,mu1',newSigma1);
discriminantScore = (log((R0./R1)))';

%PART B.1 
%threshold as a function of priors and loss value
Tgamma = log(((loss(1,2)-loss(2,2))*p1)/((loss(2,1)-loss(1,1))*p0));

%desicion and calculation of probabilities of the 4 cases 
decision = (discriminantScore <= Tgamma); % use smallest min-error threshold
ind00 = find(decision==0 & label==0); p100 = length(ind00)/Nc(1); % probability of true negative
ind10 = find(decision==1 & label==0); p110 = length(ind10)/Nc(1); % probability of false positive
ind01 = find(decision==0 & label==1); p101 = length(ind01)/Nc(2); % probability of false negative
ind11 = find(decision==1 & label==1); p111 = length(ind11)/Nc(2); % probability of true positive

%B.2
%estimate the ROC curve and find the value of tao that minimizes the probability of total error 
[ROC,tau] = estimateROC(discriminantScore,Nc,label);
probError = [((ROC(1,:)'*p0)+(ROC(3,:)'*p1))]; % probability of total error for different threshold values
[pEmin,ind] = min(probError);


% Display the estimated ROC curve with blue o
% and indicate the minimizer tau with a red +
figure(2),subplot(1,2,2), plot(ROC(1,:),ROC(2,:),'bo'); hold on,
plot(ROC(1,ind),ROC(2,ind),'r+'); 
axis equal, xlim([0,1]); ylim([0,1]),xlabel('P False Positive'),ylabel('P True Positive');
title('ROC Curve Part B');

%B.3

TotalPError1 = p110*p0+p101*p1;
disp(strcat('P Detect = ',num2str(1-TotalPError1))),  
disp(strcat('P error = ',num2str(TotalPError1))),
disp(strcat('theo gamma = ',num2str(Tgamma)));


disp(strcat('P Detection2 = ',num2str(1-pEmin))),
disp(strcat('P error2 = ',num2str(pEmin))),
disp(strcat('Gamma = ',num2str((tau(ind))))); 

%Part C
disp("Part C");
figure(3),subplot(1,3,1), plot3(x0(:,1),x0(:,2),x0(:,3),'.b'); axis equal, hold on;
figure(3),subplot(1,3,1), plot3(x1(:,1),x1(:,2),x1(:,3),'.r'); axis equal,hold on;
title ('Data');

Emu0 = mean(x0);
Esigma0 = cov(x0);
Emu1 = mean(x1);
Esigma1 = cov(x1);

Sb = (Emu0-Emu1)*(Emu0-Emu1)';
Sw = Esigma0+Esigma1;

[V,D] = eig(inv(Sw)*Sb); 
[~,ind] = sort(diag(D),'descend');
w = V(:,ind(1));

y = w'*x';

wLDA = sign(mean(y(find(label==1)))-mean(y(find(label==0))))*w; % ensures class1 falls on the + side of the axis
discriminantScore = sign(mean(y(find(label==1)))-mean(y(find(label==0))))*y; % flip yLDA accordingly
% Estimate the ROC curve for this LDA classifier
[ROC,tau] = estimateROCLDA(discriminantScore,label);
probError = [ROC(1,:)',1-ROC(2,:)']*Nc'/N; % probability of error for LDA for different threshold values
[pEmin,ind] = min(probError);
% Display the estimated ROC curve for LDA and indicate the operating points
% with smallest empirical error probability estimates (could be multiple)
figure(3), subplot(1,2,2),plot(ROC(1,:),ROC(2,:),'bo'); hold on,
plot(ROC(1,ind),ROC(2,ind),'r+'); 
axis equal, xlim([0,1]); ylim([0,1]),xlabel('P False Positive'),ylabel('P True Positive');
title('ROC LDA Part C');

%C.3

disp(strcat('P detect = ',num2str(1-pEmin))),  
disp(strcat('P error = ',num2str(pEmin))),
disp(strcat('gamma = ',num2str(tau(ind))));



function [ROC,tau] = estimateROC(discriminantScore,Nc,label)
% Generate ROC curve samples
sortedScore = sort(discriminantScore,'ascend');
tau = [sortedScore(1)-1,(sortedScore(2:end)+sortedScore(1:end-1))/2,sortedScore(end)+1];
%thresholds at midpoints of consecutive scores in sorted list
for k = 1:length(tau)
    decision = (discriminantScore <= tau(k));
    ind00 = find(decision==0 & label==0); p00 = length(ind00)/Nc(1); % probability of true negative
    ind10 = find(decision==1 & label==0); p10 = length(ind10)/Nc(1); % probability of false positive
    ind01 = find(decision==0 & label==1); p01 = length(ind01)/Nc(2); % probability of false negative
    ind11 = find(decision==1 & label==1); p11 = length(ind11)/Nc(2); % probability of true positive 
    ROC(:,k) = [p10;p11;p01;p00];    
end
end


%ROC estimation function
function [ROC,tau] = estimateROCLDA(discriminantScore,label)
% Generate ROC curve samples
Nc = [length(find(label==0)),length(find(label==1))];
sortedScore = sort(discriminantScore,'ascend');
tau = [sortedScore(1)-1,(sortedScore(2:end)+sortedScore(1:end-1))/2,sortedScore(end)+1];
%thresholds at midpoints of consecutive scores in sorted list
for k = 1:length(tau)
    decision = (discriminantScore >= tau(k));
    ind10 = find(decision==1 & label==0); p10 = length(ind10)/Nc(1); % probability of false positive
    ind11 = find(decision==1 & label==1); p11 = length(ind11)/Nc(2); % probability of true positive
    ROC(:,k) = [p10;p11];
end
end 
