function [Window] = Hamming(Samples)
%Hamming -
%       Returns a hamming window spanning the given number of samples
a0 = 0.54;
b = 1-a0;

n = 0:Samples;
Window = a0-b*cos((2 * pi * n)/(Samples-1));
end

