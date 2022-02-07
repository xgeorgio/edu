function [ Qvec, Pvec ] = pbots_qlr_update( Qvec0, Pvec0, idx, gain )
% Package: Reinforcement learning example
% File:    RL actions update
%
% Author: Harris Georgiou (c) 2016

Qvec=Qvec0;
Pvec=Pvec0;

Na=length(Pvec);  rest=[1:idx-1 idx+1:Na];

Pvec(idx)  = (1-Qvec(1))*Pvec(idx) + (1-Qvec(2))*(gain-Qvec(4));
Pvec(rest) = (1-Qvec(1))*Pvec(rest) + (Qvec(2)/Na)*(gain-Qvec(4));
Qvec(4) = Qvec(3)*Qvec(4) + (1-Qvec(3))*gain;

zidx=Pvec<0;  Pvec(zidx)=0;
zidx=Qvec<0;  Qvec(zidx)=0;

if (sum(Pvec)~=0), 
    Pvec=Pvec/sum(Pvec);
end;

end
