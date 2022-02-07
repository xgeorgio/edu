% Package: Reinforcement learning example
% File:    Environment setup
%
% Description: This is a minimal implementation of the core RL
%       rule-based update/select action scheme, using a simple
%       2x2 zero-sum game example to illustrate the gradual 
%       convergence towards stability.
%     
% Author: Harris Georgiou (c) 2016

clear all;

Nr=100;  Nc=100;

flag_useState=1;
imgfilenameDT='picobots-state.png';
imgfilenameSM='picobots-state.jpg';

Nlimit=6000;

GV=zeros(2,2,2);    % set up the game matrix (payoffs) 
GV(1,1,1:2)=[3 3];
GV(1,2,1:2)=[1 4];
GV(2,1,1:2)=[4 1];
GV(2,2,1:2)=[2 2];

Nq=size(GV,1);      % # of actions (moves) for each Bot

Bots=zeros(Nr,Nc,5+Nq);     % 1...4: RL params (gamma, epsilon, lambda, alpha), 5: Energy, 
                            % 6...(5+Nq-1): Propensities (Nq: # of actions)
Bots_img=zeros(Nr,Nc,3);    % 1...3: RGB channels
Env=zeros(Nr,Nc);           % 1: terrain slope
