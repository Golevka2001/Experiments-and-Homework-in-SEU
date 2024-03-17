vlog -work work EX_3_1.vwf.vtvsim -novopt -c -t 1ps -L cycloneiv_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.EX_3_1_vlg_vec_tst -voptargs="+acc"
add wave /*
run -all
