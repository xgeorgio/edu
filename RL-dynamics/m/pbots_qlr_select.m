function idx = pbots_qlr_select( Pvec, selmode )
% Package: Reinforcement learning example
% File:    RL action selection
%     
% Author: Harris Georgiou (c) 2016

if (selmode==0),
    [~,idx]=max(Pvec);
else
    rm=rand;
    idx=1;  sm=0;
    while ((sm<rm)&&(idx<=length(Pvec))),
        sm=sm+Pvec(idx);
        idx=idx+1;
    end;
    if (idx>=length(Pvec)), idx=randi(length(Pvec)); end;
end;

end

