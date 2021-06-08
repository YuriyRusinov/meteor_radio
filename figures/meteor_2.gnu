set terminal pdf color
set output "meteor_2st.pdf"

set xlabel 'station base, meters'
set ylabel 'transition time, seconds'

plot "meteor_2_st_sec_1.dat" w l
