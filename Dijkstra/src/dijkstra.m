%......................................................
%
%    DIJKSTRA Algorithm: Example of implementation
%
%    Harris Georgiou (c) 2007, xgeorgio@di.uoa.gr
%
%......................................................


clear all;

N=7;                % size of graph
cost_inf=inf;       % set max cost value

startV=1;           % set starting node

dist=ones(N,N)*cost_inf;    % initialize cost matrix

% set directed graph connection costs (current configuration)
dist(1,3)=8;
dist(1,4)=11;
dist(1,6)=6;
dist(2,6)=9;
dist(2,5)=8;
dist(2,7)=16;
dist(3,4)=3;
dist(3,2)=7;
dist(4,3)=10;
dist(4,5)=5;
dist(5,2)=12;
dist(5,7)=14;
dist(6,4)=4;
dist(6,5)=11;

% display currect setup
disp('DIJKSTRA Algorithm - Shortest path');
disp('..................................');

if (min(min(dist))<0),
    disp(' ');
    disp('Warning: negative values in dist(.) matrix');
end;
N
disp('Graph connections and distances:');
disp(dist);

disp('Processing...');

% initialize variables
V=[1:1:N];
S=[];
Q=[];
D=zeros(1,N);
p=zeros(1,N);

iterLog=[];

%... step-1: initialization ...
y=startV;           % current node
S=[y];              % set of "closed" nodes
Q=setdiff(V,S);     % set of "open" nodes
D(Q)=cost_inf;      % distance costs vector
D(y)=0;
p(y)=0;             % "previous" node pointer

iterCount=0;        % iteration counter

while (size(Q,2)>0),        % while there are still "open" nodes
    iterCount=iterCount+1;
    
    %... step-2: revision of D(.) values ...
    A=[];
    for x=1:N,
        if (dist(y,x)<cost_inf),  A=union(A,x);  end;
    end;
    A=intersect(A,Q);       % find current adjucent "open" nodes
    
    while (size(A,2)>0),
        x=A(1);  A=setdiff(A,x);
        
        if (D(x)>D(y)+dist(y,x)),  p(x)=y;  end;        % update path if cost is better

        D(x)=min([D(x),D(y)+dist(y,x)]);                % update distance if cost is better
    end;
    
    %... step-3: select next "closed" node ...
    DQ=D(Q);
    [minD,minI]=min(DQ);
    u=Q(minI);
    
    y=u
    S=union(S,y);
    Q=setdiff(Q,y);

    % record current status and continue
    iterLog(iterCount).iterCount=iterCount;
    iterLog(iterCount).S=S;
    iterLog(iterCount).Q=Q;
    iterLog(iterCount).y=y;
    iterLog(iterCount).D=D;
    iterLog(iterCount).p=p;

    %... step-4: continue loop, check for finish ...
end;

disp(' ');
disp('RESULTS:');
disp(' ');

I=[1:1:N];
disp('Graph nodes:');  disp(I);
disp('Best distance from start:');  disp(D);
disp('Shortest path connections:');  disp(p);
