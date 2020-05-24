grefunction [timeScale, wave] = Sinusoid(f ,a, fs, n, scale, dc, phaseShift)
%frequency, amplitude, sample rate, number of samples, scale, dc

dT = 1/fs;                        %sample rate
T = (n-1)/fs;                         %total time
timeScale = 0:dT:T / scale;       % calculate time base values (from starting time (0) to end time (T) in DT sized stepts
theta = 2*pi*f*timeScale;         % calculate angle values

wave = a * sin(theta + (phaseShift/180)*pi) + dc;

end

