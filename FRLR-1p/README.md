Title:<br/>
<b>FRLR-1p: 1-pass Fixed Rate Linear Resampler.</b>

Description:<br/>
<p>This is a simple 1-pass fixed rate linear resampler in Matlab. Specifically, it can be used as-is or as base for a function, which take a series of pairs <t,x> and a requested fixed resampling rate and it produces a new series of <t',x'> using stepwise linear regressors.</p>
<p>The resampling process normally includes a data sorting step against <t>, which is not implemented here internally and can be removed if the input data are already expected to be sorted. In the case of no sorting step, the process is completely 1-pass, which means that all elements of the two input vectors (reference points) are read only once for the entire resampling process. This is particularly useful when this implementation is to be applied directly to extremely large input files (e.g. rows in .csv) with only minimal memory usage for the calculations and only sequential read mode for speed.</p>
<p>There are two reference implementations, for Matlab/Octave (complete script) and for ANSI C (skeleton-only for CLI application).</p>
<p>This package is also available in <a href="https://github.com/DataStories-UniPi/1pass-FixedRate-LinearResampler">Datastories-Unipi repository in Github</a>.</p>
