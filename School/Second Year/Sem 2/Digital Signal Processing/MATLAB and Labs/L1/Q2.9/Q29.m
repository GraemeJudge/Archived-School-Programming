x = 0: pi/100 : 2*pi;

wave1 = sin(x*10);
wave2 = sin(x*10) + cos(x*14);

figure(1);
stem(wave1);
title('Wave 1');

figure(2);
stem(wave2);
title('Wave 2');