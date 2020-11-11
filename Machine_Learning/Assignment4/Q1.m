clear all, close all 
%Datasets
[xtrain,ytrain] = exam4q1_generateData(1000,1);
[xtest,ytest] = exam4q1_generateData(10000,2);

%number of perceptrons
Np = C_V(xtrain,ytrain);

%train and test the NN
p = NNtrain(xtrain,ytrain,Np,10000);
[TE,H] = NNtest(p,xtest,ytest,10000);

figure(3), plot(xtest,ytest,'b.'),hold on,
xlabel('X'), ylabel('Y'), title('Prediction of y (RED) over Test Data(BLUE)');
figure(3), plot(xtest,H,'r.'),hold off;

figure (4),subplot(1,2,1),plot(xtrain,ytrain,'.'),title ('Training Data 1k Samples'),
subplot(1,2,2),plot(xtest,ytest,'.'),title('Test Data 10k Samples');

%Cross-Validation with 10-fold to estimate number of perceptrons 
function order = C_V(x,y)
    s = length(x)/10;
    done = 0;
    Np = 0;
    currentScore = inf;
    
    while ~done 
        Np = Np+1;
        orderMSE = 0;
        %10-fold
        for k = 1:10
            x_validate = [];
            x_train = [];
            y_validate = [];
            y_train = [];
            if k == 1
               x_validate = x([1:(k*s)]);
               x_train = x([(k*s+1):end]);
               y_validate = y([1:(k*s)]);
               y_train = y([(k*s+1):end]);
               
            elseif k == 10 
               x_validate = x([(length(x)-s+1):end]);
               x_train = x([1:(length(x)-s)]);
               y_validate = y([(length(x)-s+1):end]);
               y_train = y([1:(length(x)-s)]);
               
            else 
                x_train = x([1:(((k-1)*s))]);
                x_validate = x([(((k-1)*s)+1):(k*s)]);
                x_train = [x_train x([(k*s+1):end])];                
                y_train = y([1:(((k-1)*s))]);
                y_validate = y([(((k-1)*s)+1):(k*s)]);
                y_train = [y_train y([(k*s+1):end])];
            end
            p = NNtrain(x_train,y_train,Np,length(x_train));
            orderMSE = orderMSE + NNtest(p,x_validate,y_validate,length(x_validate));
            k
        end
        NewScore  = orderMSE/10
        if NewScore > currentScore;
            done = 1;
        else 
            currentScore = NewScore;
        end 
        Np
    end 
    order = Np-1;
    currentScore
end
%Test the NN estimated with a new 10k samples dataset 
function [E,h] = NNtest(p,x,y,N)
    p.w2 = p.w2';
    h = MLP1L(x,p);
    E = sum((y-h).*(y-h),2)/N;   
end
%Train the NN by estimating its parameters
function p = NNtrain(x,y,Np,N)
   
    for t = 1:10
        %initialize the parameters randomly
        p.w1 = rand(Np,1); 
        p.b1 = rand(Np,1);
        p.w2 = rand(1,Np);
        p.b2 = rand(1,1);
        vecPinit = [p.w1(:);p.b1(:);p.w2(:);p.b2(:)];
        options = optimset('MaxIter',1e15*length(vecPinit));
        [Ep, val] = fminsearch (@(Ep)(MSE(x,Ep,y,Np,N)),vecPinit,options);

        p.w1 = Ep(1:Np);
        p.b1 = Ep((Np+1):(2*Np));
        p.w2 = Ep((2*Np+1):(3*Np));
        p.b2 = Ep((3*Np+1):end);
        scores(t) = val;
        allp(t) = p; 
    end 
    [~,Min] = min(scores);
    
    p = allp(Min);
end 
%MSE calculator and function for fminsearch  
function E = MSE(D,vecp,y,Np,N)
    p.w1 = vecp(1:Np);
    p.b1 = vecp((Np+1):(2*Np));
    p.w2 = (vecp((2*Np+1):(3*Np)))';
    p.b2 = vecp((3*Np+1):end);
    h = MLP1L(D,p);
    %MSE 
    E = sum((y-h).*(y-h))/N;
end 
%1 layer MLP 
function h = MLP1L(D,p)
    %First Layer softplus activation function
    softP = @(r) (1+exp(r));
    logic = @(r) 1./(1+exp(-r)); 
    x = p.w1*D + p.b1;
    %z = logic(x);
    z = softP(x);
    h = p.w2*z + p.b2;
end
%Generate Data 
function [x,y] = exam4q1_generateData(N,i)
x = gamrnd(3,2,1,N);
z = exp((x.^2).*exp(-x/2));
v = lognrnd(0,0.1,1,N);
y = v.*z;
figure(i), plot(x,y,'b.'),hold on,
xlabel('x'); ylabel('y');
end 
