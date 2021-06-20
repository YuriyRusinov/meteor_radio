set terminal svg
set output "meteor_3st.svg"

set xlabel 'station base, meters'
set ylabel 'transition time, seconds'

plot "meteor_3_st_0.dat" w p
