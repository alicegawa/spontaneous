COMMENT
Since this is an electrode current, positive values of i depolarize the cell
and in the presence of the extracellular mechanism there will be a change
in vext since i is not a transmembrane current but a current injected
directly to the inside of the cell.
ENDCOMMENT

NEURON {
    POINT_PROCESS GaussianNoise
    RANGE del, dur, amp, i, R, forRand, forRand2, tmp, counter, flag, max, min, ave, loop, ave_v
    ELECTRODE_CURRENT i
}
UNITS {
    (nA) = (nanoamp)
    (mV) = (millivolt)
}

PARAMETER {
    del (ms)
    dur (ms)	<0,1e9>
    amp (nA)
    R = 2000:daitai 2Hz ni natta yo!
    forRand = 0.01
    forRand2 = 0.01
    tmp  = 0
    counter = 0
    flag = 0
    max = -10000.0
    min = 1000.0
    ave = 0.0
    loop = 0
    ave_v = 0.0
}
ASSIGNED { 
    i (nA) 
    v (mV)
}

INITIAL {
    i = 0
    VERBATIM
    /*srand((unsigned)time(NULL));*/
    srand(25525);
    ENDVERBATIM
}


BREAKPOINT {
    loop = loop + 1
    at_time(del)
    at_time(del+dur)
    VERBATIM
    forRand = ((double)(rand()+1.0))/((double)RAND_MAX+2.0);
    forRand2 = ((double)(rand()+1.0))/((double)RAND_MAX+2.0);
    amp = sqrt( -2.0 * log(forRand))*sin(2.0*3.141593*forRand2);
    amp = amp/R;
    /*printf("amp = %lf\n",amp);*/
    ENDVERBATIM

    if (t < del + dur && t >= del) {
	i = amp
	:printf("i = %g (nA)\n",i)
    }else{
	i = 0
    }
    :printf("v = %g\n",v)
    if(v>0){
	if(flag==0){
	    counter = counter + 1
	    VERBATIM
	    usleep(1);
	    ENDVERBATIM
	}
	flag = 1
    }else{
	if(flag==1){
	    flag = 0
	}
    }
    VERBATIM
    if(max<amp){
	max = amp;
    }
    if(min>amp){
	min = amp;
    }
    /*ave = ave + amp;*/
    /*ave_v = ave_v + v;*/
    /*printf("ave_v = %lf \n",ave_v/(double)loop);*/
    /*printf("max = %lf \t min = %lf\t current average = %lf\n",max,min,ave/(double)loop);*/
    ENDVERBATIM
    :printf("counter = %g\n",counter)
}
