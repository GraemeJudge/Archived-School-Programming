function [wave] = LinCombo(inWave1, scale1, inWave2, scale2, inWave3, scale3, inWave4, scale4)
    % inWave1, scale1, inWave2, scale2, inWave5, scale5, inWave4, scale4
    wave = ((scale1 .* inWave1) + (scale2 .* inWave2) + (scale3 .* inWave3) + (scale4 .* inWave4));
end

