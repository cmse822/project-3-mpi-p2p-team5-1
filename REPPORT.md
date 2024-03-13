# Project 3: Team 5

## Part 1:

## Part 2:

## Part 3:

In this section, we've implemented the MPI ring shift with blocking using the MPI_Sendrecv() commands on a series of different process counts to compute bandwidth as a function of message sizes.  We extended the message sizes to be from 2:4096 to be from 2:2097152 (2^21) because message sizes up to 4096 did not show distinct differences in latency or bandwidth among the different nodes.  Below are plots on log-log scale, as well as linear, for better interpretability. The general trends indicate, with the exception of a processor count of two, a direct increasing power-law relationship between bandwidth and message size. Process count two shows a lot of variability over the message sizes and significantly higher bandwidth performance for message sizes up to around 4096 bytes.  Under the blocking regime, we see that as the message sizes scale, at least over the range we have plotted, there not clear improvements to bandwidth performance as we scale our process counts.  Initially, the start-up costs of communication are less for lower process counts, like for process count two, thus showing that they are able to communicate more information at a faster rate than the other process counts.  The main point here being that commnication between two processes can achieve notably higher bandwidth (at lower message sizes) likely due to fewer communication costs among the different nodes.  Above two process counts, the efficiency of parallelization appears to scale relatively similarly.
 
![Bandwidth Log-Log Scale](Part3/p_3_bdwdth_v_mssgsze_log_log_scale.png "Bandwidth Log-Log Scale")

![Bandwidth Linear Scale](Part3/p_3_bdwdth_v_mssgsze_linear_scale.png "Bandwidth Linear Scale")

Below is latency as a function of message size across varying process counts. Almost in perfect order we see the latency drop in order of the process count as message sizes increase.  The explanation to this is likely that increased processor counts improve the latency scaling due to the ability to distribute the load of the task more efifciently.

![Latency Linear Scale](Part3/p_3_latency_v_mssgsze_linear_scale.png "Latency Linear Scale")

## Part 4:

Below are the outputs replicated from Part 3 under the MPI_Irecv() and MPI_Isend() commands that use non-blocking calls.  In this instance, we see that process count two dominates again for message sizes up to approximatley 2^12, but larger process counts begin to have higher behavior in the long-run behavior.  

![Bandwidth Log-Log Scale](Part4/p_4_bdwdth_v_mssgsze_log_log_scale.png "Bandwidth Log-Log Scale for Part 4")

![Bandwidth Linear Scale](Part4/p_4_bdwdth_v_mssgsze_linear_scale.png "Bandwidth Linear Scale for Part 4")

Like in Part 3, we see under the non-blocking call regime the same long-run behavior in that there is likely a higher level of overhead communication costs when message sizes are low and process counts are high, but in the long-run, we get lowest latency for higher process counts and the highest for fewer process counts.

![Latency Linear Scale](Part4/p_4_latency_v_mssgsze_linear_scale.png "Latency Linear Scale for Part 4")
