% Package: Reinforcement learning example
% File:    Test run
%
% Description: This is a minimal implementation of the core RL
%       rule-based update/select action scheme, using a simple
%       2x2 zero-sum game example to illustrate the gradual 
%       convergence towards stability.
%     
% Author: Harris Georgiou (c) 2016

clear all;

Niter=100;

GV=[1 4 1; 2 2 2];  GV=GV/4;

Pvec0=ones(1,3);  Pvec0=Pvec0/sum(Pvec0);
Qvec0=[0.1 0.05 0.9 0];
State=zeros(1:Niter,length(Pvec0)+3);

Pvec=Pvec0;  Qvec=Qvec0;

for k=1:Niter,
    idx=pbots_qlr_select(Pvec,1);
    
    gain=randn;
    %if (idx==2), gain=abs(gain)/5; end;
    %if (idx==2), gain=0.1; else gain=0; end;
    if (gain>=0), gain=GV(1,idx); else gain=GV(2,idx); end; 
    
    [Qvec,Pvec]=pbots_qlr_update(Qvec,Pvec,idx,gain);

    State(k,:)=[Pvec Qvec(4) gain idx];
    disp(State(k,:));
end;

figure(1);
plot(1:Niter,State(:,1),'c-',1:Niter,State(:,2),'b-',1:Niter,State(:,3),'g-',1:Niter,State(:,4),'m-',1:Niter,State(:,5),'r:');
msg=sprintf('RL-progress: asymptotic plots (gam=%.3f / eps=%.3f / lam=%.3f)',Qvec(1:3));
title(msg);
legend('p1(n)','p2(n)','p3(n)','a(n)','gain(n)','Location','SouthOutside','Orientation','horizontal');
xlabel('iterations (n)');
ylabel('value');
grid on;
