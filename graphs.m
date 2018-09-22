%%
threads = [1 2 4 8 16 32];
input1 = [0.963 1.10 1.08 1.35 1.26 1.26];
input2 = [1.79 1.99 2.049 2.39 2.39 2.68];
input3 = [0.076 0.0739 0.0859 0.11 0.098 0.10];

figure
plot(threads, input1, 'LineWidth', 4);
title('Input 1 Computation Time')
xlabel('Number of Threads')
ylabel('Computation Time')
set(gca, 'FontSize', 20)

figure
plot(threads, input2, 'LineWidth', 4);
title('Input 2 Computation Time')
xlabel('Number of Threads')
ylabel('Computation Time')
set(gca, 'FontSize', 20)

figure
plot(threads, input3, 'LineWidth', 4);
title('Input 3 Computation Time')
xlabel('Number of Threads')
ylabel('Computation Time')
set(gca, 'FontSize', 20)

loadMiss = [101543780 107585278 121508561 119899747 123115718 133577103];
cacheMiss = [46698195 60045286 109269553 131284732 145487630 164970880];
figure
plot(threads, loadMiss, 'LineWidth', 4);
title('Input 2 L1 Cache Load Miss Count')
xlabel('Number of Threads')
ylabel('Load Misses')
set(gca, 'FontSize', 20)

figure
plot(threads, cacheMiss, 'LineWidth', 4);
title('Input 2 Cache Miss Count')
xlabel('Number of Threads')
ylabel('Cache Misses')
set(gca, 'FontSize', 20)

%% Second try
clear all
close all
%%
threads = [1 2 4 8 16 32];
input1 = [0.92 0.640943 0.488731 0.470809 0.48753 0.461304];
input2 = [1.67977 1.34963 1.19789 1.17699 1.16104 1.19294];
input3 = [0.0675327 0.0520888 0.0393389 0.0417547 0.0442272 0.0394191];
speedup = [0.92./input1; 1.67./input2; 0.0675./input3];
efficiency = [speedup(1,:)./threads; speedup(2,:)./threads; speedup(3,:)./threads];

figure
plot(threads, input1, 'LineWidth', 4);
title('Input 1 Computation Time')
xlabel('Number of Threads')
ylabel('Computation Time')
set(gca, 'FontSize', 20)

figure
plot(threads, input2, 'LineWidth', 4);
title('Input 2 Computation Time')
xlabel('Number of Threads')
ylabel('Computation Time')
set(gca, 'FontSize', 20)

figure
plot(threads, input3, 'LineWidth', 4);
title('Input 3 Computation Time')
xlabel('Number of Threads')
ylabel('Computation Time')
set(gca, 'FontSize', 20)

figure
plot(threads, speedup, 'LineWidth', 4);
title('Speedup')
xlabel('Number of Threads')
ylabel('Speedup')
legend('Input 1', 'Input 2', 'Input 3')
set(gca, 'FontSize', 20)

figure
plot(threads, efficiency, 'LineWidth', 4);
title('Efficiency')
xlabel('Number of Threads')
ylabel('Efficiency')
legend('Input 1', 'Input 2', 'Input 3')
set(gca, 'FontSize', 20)

loadMiss = [38366148 39591794 45986579 40130272 37842647 40920748];
cache = [84144332 86115834 88242347 90217624 85143211 85029710];
figure
plot(threads, loadMiss, 'LineWidth', 4);
title('Input 1 L1 Cache Load Miss Count')
xlabel('Number of Threads')
ylabel('Load Misses')
set(gca, 'FontSize', 20)

figure
plot(threads, cache, 'LineWidth', 4);
title('Input 1 Cache References Count')
xlabel('Number of Threads')
ylabel('Cache References')
set(gca, 'FontSize', 20)