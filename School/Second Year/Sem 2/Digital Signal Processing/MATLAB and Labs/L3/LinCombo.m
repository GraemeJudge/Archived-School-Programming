function [wave] = LinCombo(inWave1, scale1, inWave2, scale2, offset)
    % inWave1, scale1, inWave2, scale2, offset
    wave = ((scale1 .* inWave1) + (scale2 .* inWave2)) + offset;
end

