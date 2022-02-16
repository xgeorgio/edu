Title:<br/>
<b>Gene: Compact implementation of DNA/RNA gene processing in Java</b>

Description:<br/>
<p>This is a memory-efficient implementation of DNA/RNA gene container and basic processing. The main use is providing bit-level storage for the codons (6-bit), efficient codon decoding via hashmap in O(1) instead of binary trees or nested if-then, robust binary and text mode file I/O, as well as skeleton implementations for basic inherited functionality for threading, serialization, etc.</p>
The main features of this Gene class are:
<ul>
    <li>Compact bit-level storage of codons (6-bit) via standard BitSet.</li>
	<li>Efficient DNA/RNA codon decoding via statically-initialized Hashmap.</li>
	<li>Conversions to and from binary strings for export/import.</li>
	<li>Conversions to and from nucleo-bases for export/import.</li>
	<li>Utility functions for export to string, hex representation, etc.</li>
	<li>Overrides to inherited clone(), equals(), hashCode(), etc.</li>
	<li>File I/O from and to text mode storage.</li>
	<li>File I/O from and to binary storage.</li>
</ul>
