set terminal png size 1920, 1080
set output "plot_10k.png"
plot "data_10k.txt" using 1:2 with lines
unset output