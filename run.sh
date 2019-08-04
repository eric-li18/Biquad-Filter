gcc biquad.c -o biquad
gcc cascade.c -o cascade
gcc unwav.c -o unwav
gcc towav.c -o towav

case "$1" in
	-b)
		echo -e "Running biquad pipeline...\n"
		./unwav < ugly.wav | ./biquad 1 0 1 -0.7 0 | ./biquad 1 1.18 1 -1.58 0.81 | ./biquad 4.42e-3 1 0 0 0 | ./towav > out.wav
		;;
	-c)
		echo -e "Running cascade...\n"
		./unwav < ugly.wav | ./cascade 1 0 1 -0.7 0 1 1.18 1 -1.58 0.81 4.42e-3 1 0 0 0 | ./towav > out.wav
		;;
	-g)
		echo -e "Graphing frequencies...\n"
		./unwav < ugly.wav | head -300 > ugly.txt
		./unwav < out.wav | head -300 > out.txt
		gnuplot
		plot 'ugly.txt' with lines, 'out.txt' with lines
		;;
	*)
		echo -e "Option not recognized. Process Terminated.\nOptions:\n\t-b  runs biquad pipeline\n\t-c  runs cascade\n\t-g  plots graph of frequencies (requires gnuplot installation)"
		exit 1;
esac

echo -e "Finished"
exit 0;

