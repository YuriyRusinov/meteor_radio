set terminal svg
set output "meteor_2st.svg"

set xlabel 'station base, meters'
set ylabel 'transition time, seconds'

plot "meteor_2_st_sec_1.dat" w l
