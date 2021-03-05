for i in {0..200..5}
do
	echo "nohup ./farPPD macros/Scoring_macro_${i}.mac &>test${i}.log &" >> sim.sh
done
