function [Window] = Hanning(Samples)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

n = 0:Samples;

Window = 0.5*(1-cos((2*pi*n)/(Samples - 1)));
end

