

in = [1,2,4,7];
fprintf("Output: ");
fprintf("%d ", neighbor(in));


function [n] = neighbor(in)
    if size(in, 2) < 2
        n=[];
    else
        n = in(2:end) - in(1:end-1);
    end
end
