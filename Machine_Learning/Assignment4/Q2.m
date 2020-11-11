clear all, close all;
%Datasets
[xtrain,labeltrain] = generateMultiringDataset(2,1000,1);
[xtest,labeltest] = generateMultiringDataset(2,10000,2);

%Estimate hyperparameters 
[sigma,c] = C_V(xtrain,labeltrain);

%Train and validate the model
svm = fitcsvm(xtrain',labeltrain,'BoxConstraint',c,'KernelFunction','rbf','kernelScale',sigma);
validation = svm.predict(xtest')';
%Find the probability of error and success 
indCORRECT = find(labeltest==validation);
indInCORRECT = find(labeltest~=validation);
Pcorrect = length(indCORRECT)/length(labeltest);
PIncorrect = length(indInCORRECT)/length(labeltest);

figure(3),
plot(xtest(1,indCORRECT),xtest(2,indCORRECT),'g.'), hold on,
plot(xtest(1,indInCORRECT),xtest(2,indInCORRECT),'r.'), axis equal,
title('Training Data (RED: Incorrectly Classified)'),
 
 %Cross-Validation with 10-fold to estimate hyperparameters of the SVM 
function [Esigma,Ec] = C_V(x,y)
    s = length(x)/10;
    sigmas = 10.^linspace(-2,3,14); Cs = 10.^linspace(-1,6,10);
    for sig = 1:length(sigmas)
        sigma = sigmas(sig);
        for i = 1:length(Cs)
            c = Cs(i);
            %10-fold
            for k = 1:10
                x_validate = [];
                x_train = [];
                y_validate = [];
                y_train = [];
                if k == 1
                   x_validate = x(:,[1:(k*s)]);
                   x_train = x(:,[(k*s+1):end]);
                   y_validate = y([1:(k*s)]);
                   y_train = y([(k*s+1):end]);

                elseif k == 10 
                   x_validate = x(:,[(length(x)-s+1):end]);
                   x_train = x(:,[1:(length(x)-s)]);
                   y_validate = y([(length(x)-s+1):end]);
                   y_train = y([1:(length(x)-s)]);

                else 
                    x_train = x(:,[1:(((k-1)*s))]);
                    x_validate = x(:,[(((k-1)*s)+1):(k*s)]);
                    x_train = [x_train x(:,[(k*s+1):end])];                
                    y_train = y([1:(((k-1)*s))]);
                    y_validate = y([(((k-1)*s)+1):(k*s)]);
                    y_train = [y_train y([(k*s+1):end])];
                end
                
                svm = fitcsvm(x_train',y_train,'BoxConstraint',c,'KernelFunction','rbf','kernelScale',sigma);
                validation = svm.predict(x_validate')';
                indInCORRECT = find(y_validate ~= validation); 
                PIncorrect(k)=length(indInCORRECT)/length(y_validate);
            end
            scores(sig,i)  = sum(PIncorrect)/10; 
            sig 
            i
        end  
    end
    MinP = min(scores,[],'all');
    [row,col] = find(scores == MinP);
    Esigma = sigmas(row(1));
    Ec = Cs(col(1));
end
%given function to generate data
function [data,labels] = generateMultiringDataset(numberOfClasses,numberOfSamples,i)

C = numberOfClasses;
N = numberOfSamples;
% Generates N samples from C ring-shaped 
% class-conditional pdfs with equal priors

% Randomly determine class labels for each sample
thr = linspace(0,1,C+1); % split [0,1] into C equal length intervals
u = rand(1,N); % generate N samples uniformly random in [0,1]
labels = zeros(1,N);
for l = 1:C
    ind_l = find(thr(l)<u & u<=thr(l+1));
    labels(ind_l) = repmat(l,1,length(ind_l));
end

a = [1:C].^2.5; b = repmat(1.7,1,C); % parameters of the Gamma pdf needed later
% Generate data from appropriate rings
% radius is drawn from Gamma(a,b), angle is uniform in [0,2pi]
angle = 2*pi*rand(1,N);
radius = zeros(1,N); % reserve space
for l = 1:C
    ind_l = find(labels==l);
    radius(ind_l) = gamrnd(a(l),b(l),1,length(ind_l));
end

data = [radius.*cos(angle);radius.*sin(angle)];

if 1
    colors = rand(C,3);
    figure(i), clf,
    for l = 1:C
        ind_l = find(labels==l);
        plot(data(1,ind_l),data(2,ind_l),'.','MarkerFaceColor',colors(l,:)); axis equal, hold on,
    end
end
end 
