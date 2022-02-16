Title:<br/>
<b>PicoBots: Ultra-small A-life simulator in ANSI C</b>

Description:<br/>
<p>This is an ultra-small A-life "bots" simulator for terminal (text mode) in ANSI C. The purpose of this programming exercise is to demonstrate that something as complex as reinforcement learning and zero-sum spatial board games can be implemented with minimal linked libraries and fit within a single DOS-mode (16-bit) memory segment including code and data.</p>
The main features of this single-file package are:
<ul>
    <li>Inline code replacements for standard trigonometric functions.</li>
	<li>Inline code replacement of rand() with high-quality PRNG.</li>
	<li>Baseline implementation of Q-learning adaptive per-agent logic.</li>
	<li>Baseline implementation of zero-sum spatial board gaming.</li>
	<li>Spatial sensing of local neighborhood and internal agent state.</li>
	<li>Use of qsort() upon static buffer as a replacement for priority queue.</li>
	<li>Extensive error reporting, kernel initialization, shutdown.</li>
	<li>Extensive memory use monitoring to track any memory leaks.</li>
	<li>Skeleton of action-selection within Q-learning scheme for agents.</li>
</ul>
<p>Note: Binary folder '/bin' contains two compiled versions, one created by GCC 9.3 in Windows 8.1 64-bit and one created by Turbo C 2.0 in DOSbox (16-bit). These are compilations of the exact same source code by compilers with more than four decades between them. This alone proves that, although C is not portable hardware-wise, it is extremely portable time-wise.</p>
