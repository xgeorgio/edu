
/**
 * Package: DNA sequencing and processing
 * Class: Gene
 * Description: Minimal implementation of DNA genes
 * Updated: 1-Feb-2022 19:09'
 * <p>
 * @author Harris Georgiou (c) 2022
 * @version 1.1
 * @see -
 */
 
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.BitSet;
import java.util.Collections;
import java.util.Map;
import java.util.HashMap;


/**
 * Implementation of a DNA gene
 */
public class Gene implements Cloneable {
    /**
     * Internal storage for DNA data
     */
    private byte[] seq;

    /**
     * Active length in bits
     */
    private int len;

    /**
     * Lookup hashtable (static) to translate codons to amino-acids, 
     * populated via a private member function.
     */
    public static final Map<String, String> codon_amino = initializeDict();

    /**
     * Member function (private) to populate hashtable for translating codons to amino-acids.
     * The Universal DNA codon-to-aminoacid translation table is formatted below. To use with 
     * RNA input, 'U' must be replaced with 'T' before lookup. The single-letter amino-acid
     * symbol (or '0' for Stop) can be found at the return value[4].
     * Example:  char tta_aa = dict.get("TTA").charAt(4);
     * @return initialized hastable for codon/aminoacid (key/value) translation
     */
    public static Map<String, String> initializeDict() {
        Map<String, String> dict = new HashMap<String, String>();

        dict.put("TTT","Phe/F"); dict.put("TCT","Ser/S"); dict.put("TAT","Tyr/Y"); dict.put("TGT","Cys/C");
        dict.put("TTC","Phe/F"); dict.put("TCC","Ser/S"); dict.put("TAC","Tyr/Y"); dict.put("TGC","Cys/C");
        dict.put("TTA","Leu/L"); dict.put("TCA","Ser/S"); dict.put("TAA","Stop0"); dict.put("TGA","Stop0");
        dict.put("TTG","Leu/L"); dict.put("TCG","Ser/S"); dict.put("TAG","Stop0"); dict.put("TGG","Trp/W");
    
        dict.put("CTT","Leu/L"); dict.put("CCT","Pro/P"); dict.put("CAT","His/H"); dict.put("CGT","Arg/R");
        dict.put("CTC","Leu/L"); dict.put("CCC","Pro/P"); dict.put("CAC","His/H"); dict.put("CGC","Arg/R");
        dict.put("CTA","Leu/L"); dict.put("CCA","Pro/P"); dict.put("CAA","Gin/Q"); dict.put("CGA","Arg/R");
        dict.put("CTG","Leu/L"); dict.put("CCG","Pro/P"); dict.put("CAG","Gin/Q"); dict.put("CGG","Arg/R");
                
        dict.put("ATT","Ile/I"); dict.put("ACT","Thr/T"); dict.put("AAT","Asn/N"); dict.put("AGT","Ser/S");
        dict.put("ATC","Ile/I"); dict.put("ACC","Thr/T"); dict.put("AAC","Asn/N"); dict.put("AGC","Ser/S");
        dict.put("ATA","Ile/I"); dict.put("ACA","Thr/T"); dict.put("AAA","Lys/K"); dict.put("AGA","Arg/R");
        dict.put("ATG","Met/M"); dict.put("ACG","Thr/T"); dict.put("AAG","Lys/K"); dict.put("AGG","Arg/R");

        dict.put("GTT","Val/V"); dict.put("GCT","Ala/A"); dict.put("GAT","Asp/D"); dict.put("GGT","Gly/G");
        dict.put("GTC","Val/V"); dict.put("GCC","Ala/A"); dict.put("GAC","Asp/D"); dict.put("GGC","Gly/G");
        dict.put("GTA","Val/V"); dict.put("GCA","Ala/A"); dict.put("GAA","Glu/E"); dict.put("GGA","Gly/G");
        dict.put("GTG","Val/V"); dict.put("GCG","Ala/A"); dict.put("GAG","Glu/E"); dict.put("GGG","Gly/G");

        return Collections.unmodifiableMap(dict);    // proper wrapping for 'static final' host variable
    }

    /**
     * Default constructor
     */
    public Gene() {
        seq = null;
        len = -1;
    }

    /**
     * Copy constructor
     * @param other Instance to copy from
     */
    public Gene(Gene other) {
        seq = other.toByteArray();
        len = other.getLength();
    }

    /**
     * Copy constructor with 'external' data
     * @param fromseq Source data buffer
     * @param fromlen Source length in bits
     */
    public Gene(byte[] fromseq, int fromlen) {
        if ((fromseq==null)||(fromseq.length==0)||(fromlen<0)) {    // invalid inputs, use defaults
            seq = null;
            len = -1;
        }
        else {
            int  bitsz = fromseq.length*Byte.SIZE;              // full-size buffer in bits
            seq = fromseq;
            if ((fromlen>bitsz-Byte.SIZE)&&(fromlen<bitsz))     // if last-byte fraction is valid, use it
                len = fromlen;                              
            else
                len = bitsz;                                    // otherwise assume full buffer usage
        }
    }

    /**
     * Get the bit-length of the current gene data
     * @return Length in bits
     */
    public int getLength() {
        return (len);
    }

    /**
     * Get the current gene data storage
     * @return Byte array (use with getLength())
     */
    public byte[] toByteArray() {
        return (seq);
    }

    /**
     * Read binary string into gene data storage
     * @param binstr Source binary string 
     */
    public void fromBinaryString(String binstr) {
        len = binstr.length();
        BitSet bset = new BitSet(len);      // use BitSet as temporary storage
        for (int i = 0; i < len; i++) {
            // Note: every character other than '1' is treated as '0'
            if (binstr.charAt(i) == '1')    // zero-initialized, set 1s properly
                bset.set(i);
        }
        System.out.println("DEBUG: BitSet(seq)=" + bset.toString());
        if (bset.cardinality() == 0)  // incorrect conversion from BitSet when sequence is 'AAAA...'="00000..."
            seq = new byte[(int)Math.ceil(len / (double) Byte.SIZE)];
        else
            seq = bset.toByteArray(); // convert BitSet to gene data storage (ERROR)
        System.out.println("DEBUG: seq.length=" + seq.length + " / len=" + len);        
    }

    /**
     * Get binary representation of the gene data
     * @return Binary string (exact bit length)
     */
    public String toBinaryString() {
        String s1, sb = "";
        for (int i = 0; i < seq.length; i++) {
            s1 = String.format("%8s", Integer.toBinaryString(seq[i] & 0xFF)).replace(' ', '0');
            sb = sb + (new StringBuffer(s1)).reverse().toString(); // append to the right, reversed
            //System.out.println("DEBUG: s1=" + s1 + ", sb=" + sb);
        }
        if (sb.length() > len)
            sb = sb.substring(0, len);  // truncate any trailing zeros
        else if (sb.length() < len) {
            while (sb.length() < len)
                sb = sb + "0";      // required when last base is 'A'="00"
        }
        return (sb);
    }

    /**
     * Read bases string into gene data storage
     * @param baseseq Source bases string 
     */
    public void fromBasesString(String baseseq) {
        fromBinaryString(Gene.bases_to_binaryString(baseseq));
    }

    /**
     * Get bases sequence of the gene data
     * @param isRNA Replace 'T' with 'U' if true
     * @return Bases sequence string
     */
    public String toBasesString(boolean isRNA) {
        return (Gene.binaryString_to_bases(toBinaryString(), isRNA));
    }

    /**
     * Get hexadecimal representation of the gene data, use only for compact display (output) 
     * @return Hex string (non-truncated bit length)
     */
    public String toHexString() {
        String s1, sb="";
        for (int i = 0; i < seq.length; i++)
        {
            s1 = String.format("%2s", Integer.toHexString(seq[i] & 0xFF)).replace(' ', '0').toUpperCase();
            sb=sb+(new StringBuffer(s1)).toString();  // append to the right, reversed
            //System.out.println("DEBUG: s1=" + s1 + ", sb=" + sb);
        }
        return (sb);
    }

    /**
     * Get string representation of gene data
     * @return Default string conversion
     */
    public String toString() {
        return (toHexString());     // use hex by default
    }

    /**
     * Get a clone (deep copy) of the current gene instance
     * @return New Gene instance
     */
    @Override
    public Gene clone() {
        return (new Gene(seq, len));
    }

    /**
     * Get default hash code
     * @return Hash code of instance
     */
    @Override
    public int hashCode() {
        return (Arrays.hashCode(seq));
    }

    /**
     * Get default equality comparison
     * @param other Gene to compare to
     * @return True if gene data are equal
     */
    public boolean equals(Gene other) {
        return (Arrays.equals(seq, other.toByteArray()));
    }

    /**
     * Static converter of nucleic bases to binary string
     * @param baseseq Input sequence of bases (assume not null)
     * @return Binary representation string
     */
    public static String bases_to_binaryString(String baseseq) {
        StringBuffer sbuff = new StringBuffer(baseseq.length()*2);    // pre-allocate enough space
        char[] bseq = baseseq.toUpperCase().toCharArray();
        for (int i = 0; i < bseq.length; i++) {
            switch (bseq[i]) {      // Note: first digit shows pairing (A-T, C-G)
                case 'A':
                    sbuff.append("00");
                    break;
                case 'T':       // input is DNA
                case 'U':       // input is RNA
                    sbuff.append("01");
                    break;
                case 'C':
                    sbuff.append("10");
                    break;
                case 'G':
                    sbuff.append("11");
                    break;
                default:
                    System.err.println("Error: Gene.base_tobinaryString(): Invalid input character '" + bseq[i]
                            + "' at offset " + i+" (ignored).");
                    break;
            }
        }
        return (sbuff.toString());
    }

    /**
     * Static converter of binary string to nucleic bases
     * @param binstr Binary string to translate (assume not null)
     * @param isRNA Replace 'T' with 'U' in output if true
     * @return Bases-translated string
     */
    public static String binaryString_to_bases(String binstr, boolean isRNA) {
        if (binstr.length() % 2 > 0) { // make sure full translation is possible
            System.err.println("Error: Gene.binaryString_to_bases(): Invalid binary string (incomplete).");
            return (null);
        }

        StringBuffer sbuff = new StringBuffer(binstr.length() / 2); // pre-allocate enough space
        for (int i = 0; i < binstr.length(); i = i + 2) {
            // option 1: implement more compactly, but with 1-4 comparisons per input pair (avg=2.5)
            /*if ((binstr.charAt(i) == '0') && (binstr.charAt(i + 1) == '0'))
                sbuff.append('A');
            else if ((binstr.charAt(i) == '0') && (binstr.charAt(i + 1) == '1'))
                sbuff.append('T');
            else if ((binstr.charAt(i) == '1') && (binstr.charAt(i + 1) == '0'))
                sbuff.append('C');
            else if ((binstr.charAt(i) == '1') && (binstr.charAt(i + 1) == '1'))
                sbuff.append('G');
            else
                System.err.println("Error: Gene.binaryString_to_bases(): Invalid bits pair '" + binstr.charAt(i)
                        + binstr.charAt(i + 1) + "' at offsets " + i + ":" + (i + 1)+" (ignored).");*/

            // option 2: implement as static binary tree, more extensive but solid 2 comparisons per input pair
            boolean hasErrors = false;
            if (binstr.charAt(i) == '0') {
                if (binstr.charAt(i + 1) == '0')
                    sbuff.append('A');
                else if (binstr.charAt(i + 1) == '1')
                    sbuff.append('T');
                else
                    hasErrors = true;
            } else if (binstr.charAt(i) == '1') {
                if (binstr.charAt(i + 1) == '0')
                    sbuff.append('C');
                else if (binstr.charAt(i + 1) == '1')
                    sbuff.append('G');
                else
                    hasErrors = true;
            }

            if (hasErrors) {
                System.err.println("Error: Gene.binaryString_to_bases(): Invalid bits pair '" + binstr.charAt(i)
                        + binstr.charAt(i + 1) + "' at offsets " + i + ":" + (i + 1) + " (ignored).");
                hasErrors = false;
            }
        }
        if (isRNA)
            return (sbuff.toString().replace('T', 'U'));
        else
            return (sbuff.toString());
    }

    /**
     * Static converter of nucleic bases to amino-acids
     * @param baseseq Bases string to translate (assume not null)
     * @return Translated string of amino-acids
     */
    public static String bases_to_aminoString(String baseseq) {
        if (baseseq.length() % 3 > 0) { // make sure full translation is possible
            System.err.println("Error: Gene.bases_to_aminoString(): Invalid bases string (incomplete).");
            return (null);
        }

        String aastr="";
        StringBuffer sbuff = new StringBuffer(baseseq.length() / 3); // pre-allocate enough space
        baseseq=baseseq.toUpperCase().replace('U', 'T');    // also cover RNA input translation
        for (int i = 0; i < baseseq.length(); i = i + 3) {
            aastr = codon_amino.get(baseseq.substring(i, i + 3));   // translate next codon (bases triplet)
            if (aastr != null)
                sbuff.append(aastr.charAt(4));      // use single-letter translation by default
            else
                System.err.println("Error: Gene.bases_to_aminoString(): Invalid codon '" + aastr + "' at offsets " + i
                        + ":" + (i + 2) + " (ignored).");
        }

        return (sbuff.toString());
    }    

    /**
     * Read gene data from binary file (bytes)
     * @param filename The input file to read from
     * @param maxlen Bit-length of gene data (-1 for unbounded)
     * @return New Gene instance
     */
    public static Gene readGeneFromByteFile(String filename, int maxlen) {
        try {   
            File fh = new File(filename);
            DataInputStream inpF = new DataInputStream(new BufferedInputStream(new FileInputStream(fh)));
            byte[] buff = new byte[(int) fh.length()];     // max size is max int (2GB)
            inpF.readFully(buff);
            inpF.close();
            if (maxlen <= 0)
                maxlen = buff.length*Byte.SIZE;     // set proper length if not provided
            return (new Gene(buff, maxlen));        // handle other 'maxlen' checks internally
        } catch (IOException e) {
            System.err.println("Error: readGeneFromByteFile: " + e.toString());
            return(null);
        }        
    }

    /**
     * Write gene data to binary file (bytes)
     * @param filename The output file name to write to
     * @param src The Gene instance to write
     * @return True if successful
     */
    public static boolean writeGeneToByteFile(String filename, Gene src) {
        try {
            File fh = new File(filename);
            DataOutputStream outF = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(fh)));
            outF.write(src.toByteArray());
            outF.close();
            return (true);
        } catch (IOException e) {
            System.err.println("Error: readGeneFromByteFile: " + e.toString());
            return (false);
        }
    }

    /**
     * Read gene data from text file (characters)
     * @param filename The input file to read from
     * @return New Gene instance
     */
    public static Gene readGeneFromTextFile(String filename) {
        try {
            BufferedReader fread = new BufferedReader(new FileReader(filename));
            String str = null;
            StringBuffer sbuff = new StringBuffer();
            Gene gn = new Gene();
            while ((str = fread.readLine()) != null) {      // readLine() provided by BufferedReader class
                sbuff.append(str.toUpperCase());   // suppress newline characters
            }
            fread.close();
            System.out.println("DEBUG: Base sequence retrieved is '" + sbuff.toString() + "'");
            gn.fromBinaryString(bases_to_binaryString(sbuff.toString()));
            return (gn);
        } catch (IOException e) {
            System.err.println("Error: readGeneFromTextFile: " + e.toString());
            return (null);
        }
    }

    /**
     * Write gene data to text file (characters)
     * @param filename The output file to write to
     * @param src The Gene instance to write
     * @param isRNA Replace 'T' with 'U' in output if true
     * @return True if successful
     */
    public static boolean writeGeneToTextFile(String filename, Gene src, boolean isRNA) {
        try {
            BufferedWriter fwrite = new BufferedWriter(new FileWriter(filename));
            fwrite.write(binaryString_to_bases(src.toBinaryString(), isRNA));
            fwrite.close();
            return (true);
        } catch (IOException e) {
            System.err.println("Error: writeGeneToTextFile: " + e.toString());
            return (false);
        }
    }

    
    /**
     * ---  Class main process, used for unit testing ---
     * @param args[] (not used)
     */
    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String inpS="", inpB="";

        System.out.print("enter input sequence: ");
        try {
            inpS = reader.readLine().toUpperCase();
        } catch (IOException e) {
            //...
        }
        
        System.out.println("input sequence: " + inpS+"\n");
        
        //... Test: core storage and binary/bases conversions ...
        inpB=Gene.bases_to_binaryString(inpS);
        System.out.println("binary translation: "+inpB);
        Gene gn = new Gene();
        gn.fromBinaryString(inpB);
        System.out.println("Gene byte array: " + gn.toString());
        System.out.println("Gene bits array: " + gn.toBinaryString());
        Gene gn2 = new Gene();
        //gn2.fromBinaryString(gn.toBinaryString());
        gn2.fromBasesString(gn.toBasesString(false));
        System.out.println("Translated sequence: " + gn2.toBasesString(false));
        System.out.println(
                "Test: " + gn.toBinaryString() + " == " + gn2.toBinaryString() + " ?  ->  " + (gn.equals(gn2)));
        
        //... Test: binary file I/O ...
        /*String fname = "test1.bin";
        System.out.println("Opening byte file for input: '"+fname+"'");
        Gene gn3=readGeneFromByteFile(fname,-1);
        System.out.println("Gene retrieved: seq=" + gn3.toString() + " / len=" + gn3.getLength());
        
        String fname2 = "test2.bin";
        System.out.println("Opening byte file for output: '"+fname2+"'");
        if (writeGeneToByteFile(fname2, gn3)) {
            System.out.println("\tGene written to file successfully.");
        }*/

        //... Test: text file I/O ...
        String fname3 = "test3.txt";
        System.out.println("Opening text file for input: "+fname3);
        Gene gn4=readGeneFromTextFile(fname3);
        System.out.println("Gene retrieved: seq=" + gn4.toString() + " / len=" + gn4.getLength());

        /*String fname4 = "test4.txt";
        System.out.println("Opening text file for output: "+fname4);
        if (writeGeneToTextFile(fname4, gn4, false)) {
            System.out.println("\tGene written to file successfully.");
        }*/

        System.out.println("codon_amino: items=" + codon_amino.size());
        System.out.println("codon_amino: lookup key 'TTA' -> " + codon_amino.get("TTA") + " ('"
                + codon_amino.get("TTA").charAt(4) + "')");
        System.out.println("codon_amino: translate '" + inpS + "' -> '" + Gene.bases_to_aminoString(inpS) + "'");
        
    }   // end main()

}   // end class
