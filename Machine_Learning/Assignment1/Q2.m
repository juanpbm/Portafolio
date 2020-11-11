clear all, close all,

%generate 10000 samples from 4 different gaussian pdfs
N = 10000; p = 0.25;
u = rand(1,N);
N1 = length(find(u <=0.25));
N2 = length(find((u > 0.25) & (u <=0.5)));
N3 = length(find((u > 0.5) & (u <=0.75)));
N4 = length(find(u>0.75));          
Nc = [N1 N2 N3 N4];

mu1 = [4;1]; Sigma1 = [4 -3;-3 4];
x1 = mvnrnd(mu1, Sigma1, N1);
figure(1), plot(x1(:,1),x1(:,2),'.b'); axis equal, hold on;
mu2 = [0;-2]; Sigma2 = [3 0;0 1];
x2 = mvnrnd(mu2, Sigma2, N2);
figure(1),plot(x2(:,1),x2(:,2),'.r'); axis equal,hold on;
mu3 = [-4;1]; Sigma3 = [4 3;3 4];
x3 = mvnrnd(mu3, Sigma3, N3);
figure(1), plot(x3(:,1),x3(:,2),'.k'); axis equal,hold on;
mu4 = [0;0]; Sigma4 = [1 0;0 1];
x4 = mvnrnd(mu4, Sigma4, N4);
figure(1), plot(x4(:,1),x4(:,2),'.y'); axis equal,hold on;
title ('Data'),xlim([-15,15]), ylim([-15,15]),xlabel('X1'),ylabel('X2');

%put all samples together and make the labels vector
x = [x1; x2; x3; x4]';
label = [ones(1,N1) 2*ones(1,N2) 3*ones(1,N3) 4*ones(1,N4)];

score1 = mvnpdf(x',mu1',Sigma1)*0.25;
score2 = mvnpdf(x',mu2',Sigma2)*0.25;
score3 = mvnpdf(x',mu3',Sigma3)*0.25;
score4 = mvnpdf(x',mu4',Sigma4)*0.25;

%Part A

%put the scores together to search for the maximum
R = [score1 score2 score3 score4];

[~,decision] = max(R');
%find all possible combinations of decision vs truth  
ind11 = find(decision==1 & label==1); p11 = length(ind11)/Nc(1); 
ind12 = find(decision==1 & label==2); p12 = length(ind12)/Nc(2); 
ind13 = find(decision==1 & label==3); p13 = length(ind13)/Nc(3); 
ind14 = find(decision==1 & label==4); p14 = length(ind14)/Nc(4); 

ind21 = find(decision==2 & label==1); p21 = length(ind21)/Nc(1); 
ind22 = find(decision==2 & label==2); p22 = length(ind22)/Nc(2); 
ind23 = find(decision==2 & label==3); p23 = length(ind23)/Nc(3); 
ind24 = find(decision==2 & label==4); p24 = length(ind24)/Nc(4); 

ind31 = find(decision==3 & label==1); p31 = length(ind31)/Nc(1); 
ind32 = find(decision==3 & label==2); p32 = length(ind32)/Nc(2); 
ind33 = find(decision==3 & label==3); p33 = length(ind33)/Nc(3); 
ind34 = find(decision==3 & label==4); p34 = length(ind34)/Nc(4); 

ind41 = find(decision==4 & label==1); p41 = length(ind41)/Nc(1); 
ind42 = find(decision==4 & label==2); p42 = length(ind42)/Nc(2); 
ind43 = find(decision==4 & label==3); p43 = length(ind43)/Nc(3); 
ind44 = find(decision==4 & label==4); p44 = length(ind44)/Nc(4);
%calculate the Total probability of error 
TotalPError = 1-(p11*0.25+p22*0.25+p33*0.25+p44*0.25);
%generate the confusion matrix 
ConM = [length(ind11) length(ind12) length(ind13) length(ind14);
        length(ind21) length(ind22) length(ind23) length(ind24);
        length(ind31) length(ind32) length(ind33) length(ind34);
        length(ind41) length(ind42) length(ind43) length(ind44)];
    
disp('Part A');
disp(strcat('P error = ',num2str(TotalPError)));

%Plot all the decisions made, Correct are green and incorrect are red
%Markers are: o class 1, + class 2, star class 3, triangle class 4

figure(2), 
plot(x(1,ind11),x(2,ind11),'og'); hold on,
plot(x(1,ind12),x(2,ind12),'or'); hold on,
plot(x(1,ind13),x(2,ind13),'or'); hold on,
plot(x(1,ind14),x(2,ind14),'or'); hold on,

plot(x(1,ind21),x(2,ind21),'+r'); hold on,
plot(x(1,ind22),x(2,ind22),'+g'); hold on,
plot(x(1,ind23),x(2,ind23),'+r'); hold on,
plot(x(1,ind24),x(2,ind24),'+r'); hold on,

plot(x(1,ind31),x(2,ind31),'pg'); hold on,
plot(x(1,ind32),x(2,ind32),'pr'); hold on,
plot(x(1,ind33),x(2,ind33),'pg'); hold on,
plot(x(1,ind34),x(2,ind34),'pr'); hold on,

plot(x(1,ind41),x(2,ind41),'^r'); hold on,
plot(x(1,ind42),x(2,ind42),'^r'); hold on,
plot(x(1,ind43),x(2,ind43),'^r'); hold on,
plot(x(1,ind44),x(2,ind44),'^g'); hold on,
axis equal, xlim([-15,15]), ylim([-15,15]),xlabel('X1'),ylabel('X2'),
title ('Decisions  Green Correct, Red Incorrect');

%Part B
%Loss/Cost/Risk matrix 
loss = [0 1 1 3;1 0 1 3;1 1 0 3;1 1 1 0];
% new scores taking into account the loos values
A1 = score1*loss(1,1)+score2*loss(1,2)+score3*loss(1,3)+score4*loss(1,4);
A2 = score1*loss(2,1)+score2*loss(2,2)+score3*loss(2,3)+score4*loss(2,4);
A3 = score1*loss(3,1)+score2*loss(3,2)+score3*loss(3,3)+score4*loss(3,4);
A4 = score1*loss(4,1)+score2*loss(4,2)+score3*loss(4,3)+score4*loss(4,4);


%Put the action scores together to search for the action that minimizes the %score 
Action = [A1 A2 A3 A4];
[~,decision] = min(Action');


%find all possible combinations of decision vs truth  
ind11 = find(decision==1 & label==1); p11 = length(ind11)/Nc(1); 
ind12 = find(decision==1 & label==2); p12 = length(ind12)/Nc(2); 
ind13 = find(decision==1 & label==3); p13 = length(ind13)/Nc(3); 
ind14 = find(decision==1 & label==4); p14 = length(ind14)/Nc(4); 

ind21 = find(decision==2 & label==1); p21 = length(ind21)/Nc(1); 
ind22 = find(decision==2 & label==2); p22 = length(ind22)/Nc(2); 
ind23 = find(decision==2 & label==3); p23 = length(ind23)/Nc(3); 
ind24 = find(decision==2 & label==4); p24 = length(ind24)/Nc(4); 

ind31 = find(decision==3 & label==1); p31 = length(ind31)/Nc(1); 
ind32 = find(decision==3 & label==2); p32 = length(ind32)/Nc(2); 
ind33 = find(decision==3 & label==3); p33 = length(ind33)/Nc(3); 
ind34 = find(decision==3 & label==4); p34 = length(ind34)/Nc(4); 

ind41 = find(decision==4 & label==1); p41 = 3*length(ind41)/Nc(1); 
ind42 = find(decision==4 & label==2); p42 = 3*length(ind42)/Nc(2); 
ind43 = find(decision==4 & label==3); p43 = 3*length(ind43)/Nc(3); 
ind44 = find(decision==4 & label==4); p44 = length(ind44)/Nc(4);


%calculate the Total probability of error 
TotalPError = 1-(p11*0.25+p22*0.25+p33*0.25+p44*0.25);
disp('Part B');
disp(strcat('P error = ',num2str(TotalPError)));

%Plot all the decisions made, Correct are green and incorrect are red
%Markers are: o class 1, + class 2, star class 3, triangle class 4
figure(3),  
plot(x(1,ind11),x(2,ind11),'og'); hold on,
plot(x(1,ind12),x(2,ind12),'or'); hold on,
plot(x(1,ind13),x(2,ind13),'or'); hold on,
plot(x(1,ind14),x(2,ind14),'or'); hold on,

plot(x(1,ind21),x(2,ind21),'+r'); hold on,
plot(x(1,ind22),x(2,ind22),'+g'); hold on,
plot(x(1,ind23),x(2,ind23),'+r'); hold on,
plot(x(1,ind24),x(2,ind24),'+r'); hold on,

plot(x(1,ind31),x(2,ind31),'pg'); hold on,
plot(x(1,ind32),x(2,ind32),'pr'); hold on,
plot(x(1,ind33),x(2,ind33),'pg'); hold on,
plot(x(1,ind34),x(2,ind34),'pr'); hold on,

plot(x(1,ind41),x(2,ind41),'^r'); hold on,
plot(x(1,ind42),x(2,ind42),'^r'); hold on,
plot(x(1,ind43),x(2,ind43),'^r'); hold on,
plot(x(1,ind44),x(2,ind44),'^g'); hold on,
axis equal, xlim([-15,15]), ylim([-15,15]),xlabel('X1'),ylabel('X2'),
title ('Decisions  Green Correct, Red Incorrect');
