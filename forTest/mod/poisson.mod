COMMENT
Since this is an electrode current, positive values of i depolarize the cell
and in the presence of the extracellular mechanism there will be a change
in vext since i is not a transmembrane current but a current injected
directly to the inside of the cell.
ENDCOMMENT

NEURON {
    POINT_PROCESS PoissonNoise
    RANGE del, dur, amp, i, R, forRand, forRand2, k, n, tmp_n
    ELECTRODE_CURRENT i
}
UNITS {
    (nA) = (nanoamp)
}

PARAMETER {
    del (ms)
    dur (ms)	<0,1e9>
    amp (nA)
    R = 200
    forRand = 0.01
    forRand2 = 0.01
    k = 0 :counter
    n = 0.26:2.7 :parameter to adjust
    tmp_n = 1
}
ASSIGNED { i (nA) }

INITIAL {
    i = 0
    VERBATIM
    srand((unsigned)time(NULL));
    /*srand(25525);*/
    ENDVERBATIM
}


BREAKPOINT {
    
    at_time(del)
    at_time(del+dur)
    VERBATIM
    k=0;
    forRand = ((double)(rand()+1.0))/((double)RAND_MAX+2.0);
    tmp_n = exp(n)*forRand;
    while(tmp_n>1){
	if(tmp_n==HUGE_VAL){
	    break;
	}
	forRand2 = ((double)(rand()))/((double)RAND_MAX);
	tmp_n *= forRand2;
	k = k+1;
    }
    /*k -= n;*/
    /*amp = 2*k/n;*/
    amp = k;
    ENDVERBATIM

    if (t < del + dur && t >= del) {
	i = amp
	:printf("i = %g (nA)\n",i)
    }else{
	i = 0
    }
}
