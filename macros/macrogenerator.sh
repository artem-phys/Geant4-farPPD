for i in {0..200..5}
do
	echo "/run/initialize 
 	/control/verbose
	/run/verbose 0 
	/event/verbose 0
	/tracking/verbose 0
	/gun/energy ${i} keV 
	/run/beamOn 10000000
	/control/shell mv scoring.root scoring_${i}.root " > Scoring_macro_${i}.mac
done
