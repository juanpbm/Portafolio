clear all, close all

%calculated the values that are random
n = 10; Ntrain = 50; Ntest = 1000;
a = rand(1,n);
mu = round(10*rand(1,n));
A = rand(n); sigma = A*A'+1e-3*eye(n,n);
alphaSet= 10.^linspace(-3.5,1.5,501)*trace(sigma)/n;

%vary the noise level alpha 
for EX = 1:length(alphaSet)
    
    alpha = alphaSet(EX);
    %generate data
    [xtrain,ytrain] = genData(a,mu,sigma,n,Ntrain,alpha);
    [xtest,ytest] = genData(a,mu,sigma,n,Ntest,alpha);
    %estimate the optimal Beta with Cross-Validation 
    beta = C_V(xtrain,ytrain',n);
    %estimate the parameters w with the optimal beta 
    p = mapPE(xtrain,ytrain',beta);
    %calculate the -2log-likelihood of the data with current alpha 
    utest = [ones(1,length(xtest));xtest];
    mutest = p'*utest;
    LL = 0;

    for i = 1:length(ytest)
        LL = LL - 2*log(mvnpdf(ytest(i),mutest(i),1));
    end
    
    %plot the results
    figure(1), loglog(alpha,LL,'.'), grid on, title('Results'),
    xlabel('Alpha'),ylabel('-2log-likelihood'),xlim([10^-3,10^3]), hold on;
    
    %stop once the -2log-likelihood goes to infinity 
    if LL == inf 
        disp ('-2log-likelihood has gone to inf');
        alpha 
        LL 
        break;
    end 
    
    results(:,EX) = [alpha;LL];
end 

%Cross-validation with 5-fold to find optimal beta 
function Ebeta = C_V(x,y,n)

    s = length(x)/5;
    done = 0;
    b = 0;
    currentScore = -inf;
    
    SigmaHat = cov(x');
    betaCandidates = 10.^linspace(-5,5,1001)*trace(SigmaHat)/n;
    
    while ~done & b < 1001
        b = b+1;
        LL= 0;
        beta = betaCandidates(b);
        
        %5-fold
        for k = 1:5
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
                x_train = [x_train  x(:,[(k*s+1):end])];                
                y_train = y([1:(((k-1)*s))]);
                y_validate = y([(((k-1)*s)+1):(k*s)]);
                y_train = [y_train ; y([(k*s+1):end])];
            end
            u_validate = [ones(1,length(x_validate));x_validate];
            p = mapPE(x_train,y_train,beta);
            LL = 0;
            for i = 1:length(y_validate)
                mu = p'*u_validate;
                LL = LL + log(mvnpdf(y_validate(i),mu(i),1));
            end
        end
        
        MLL  = (1/5)*LL; 
        if MLL < currentScore
            done = 1;
        else 
            currentScore = MLL;
        end 
    end 
    Ebeta = betaCandidates(b-1);
End

%MAP estimator for the parameters w
function wMAP = mapPE(xTrain,yTrain,beta)
   [n,N] = size(xTrain);
   u = [ones(1,N);xTrain];
   b = u*yTrain/N;
   A = u*u'/N + eye(n+1,n+1)/(N*beta);
   wMAP = inv(A)*b;
end 

%Generate Data 
function [x,y] = genData(a,mu,sigma,n,N,alpha)
   x = mvnrnd(mu,sigma,N);
   z = mvnrnd(zeros(1,n),alpha*eye(n),N);
   v = mvnrnd(0,1,N);
   y = a*(x' + z')+ v';
   x = x';
end 
