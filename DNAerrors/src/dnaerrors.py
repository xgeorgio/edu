# Program: DNA codon/protein decoding and error analysis
# Version: 1.0
# Author:  Harris Georgiou (c) 2022

# Universal DNA codon-to-protein decoding table
# Note(1): To use with RNA input, 'U' must be replaced with 'T' before lookup
# Note(2): Single-letter protein symbol can be found at lookup.value[4]
codon_amino = { "TTT": "Phe/F",  "TCT": "Ser/S",  "TAT": "Tyr/Y",  "TGT": "Cys/C", 
                "TTC": "Phe/F",  "TCC": "Ser/S",  "TAC": "Tyr/Y",  "TGC": "Cys/C",
                "TTA": "Leu/L",  "TCA": "Ser/S",  "TAA": "Stop0",  "TGA": "Stop0",
                "TTG": "Leu/L",  "TCG": "Ser/S",  "TAG": "Stop0",  "TGG": "Trp/W",
                
                "CTT": "Leu/L",  "CCT": "Pro/P",  "CAT": "His/H",  "CGT": "Arg/R",
                "CTC": "Leu/L",  "CCC": "Pro/P",  "CAC": "His/H",  "CGC": "Arg/R",
                "CTA": "Leu/L",  "CCA": "Pro/P",  "CAA": "Gin/Q",  "CGA": "Arg/R",
                "CTG": "Leu/L",  "CCG": "Pro/P",  "CAG": "Gin/Q",  "CGG": "Arg/R",
                
                "ATT": "Ile/I",  "ACT": "Thr/T",  "AAT": "Asn/N",  "AGT": "Ser/S",
                "ATC": "Ile/I",  "ACC": "Thr/T",  "AAC": "Asn/N",  "AGC": "Ser/S",
                "ATA": "Ile/I",  "ACA": "Thr/T",  "AAA": "Lys/K",  "AGA": "Arg/R",
                "ATG": "Met/M",  "ACG": "Thr/T",  "AAG": "Lys/K",  "AGG": "Arg/R",

                "GTT": "Val/V",  "GCT": "Ala/A",  "GAT": "Asp/D",  "GGT": "Gly/G",
                "GTC": "Val/V",  "GCC": "Ala/A",  "GAC": "Asp/D",  "GGC": "Gly/G",
                "GTA": "Val/V",  "GCA": "Ala/A",  "GAA": "Glu/E",  "GGA": "Gly/G",
                "GTG": "Val/V",  "GCG": "Ala/A",  "GAG": "Glu/E",  "GGG": "Gly/G"  }


def codon_to_amino( codon, isRNA=False ):
    '''Codon/amino lookup wrapper with uppercase and RNA conversions
       codon : (string) base triplet to lookup 
       isRNA=True : replace 'U' with 'T' before lookup
       return : protein label or None if not found'''
    codon = codon.upper()
    if (isRNA):
        codon = codon.replace('U','T')    # replacement for RNA -> DNA
    if (codon in codon_amino.keys()):
        return(codon_amino[codon])
    else:
        return (None)


def amino_to_codon( amino, isRNA=False ):
    '''Amino/codon lookup wrapper with RNA conversions
       amino : (string) protein label entry in table
       isRNA=True : replace 'T' with 'U' after lookup
       return : list of valid codons for given protein'''
    if (amino in codon_amino.values()):
        codons = []
        for (k,v) in codon_amino.items():
            if (v==amino):
                if (isRNA):
                    k = k.replace('T','U')    # replacement for DNA -> RNA
                codons = codons + [k]
        return (codons)
    else:
        return (None)


def count_errors( codon1, codon2 ):
    '''Compare two codons (base triplets) and count differences'''
    errcount = 0
    for i in range(3):
        if codon1[i]!=codon2[i]:
            errcount = errcount + 1
    return errcount


# -----  Main program (run as script)  -----
if __name__ == "__main__" :
    print('DNA codon/protein decoding and error analysis')
    print('Harris Georgiou (c) 2022\n')

    # step-1: generate all codons, lookup in table and display
    for a in ['T','C','A','G']:
        for c in ['T','C','A','G']:
            for b in ['T','C','A','G']:
                codon = a+b+c    # preserve cell order as in table definition above
                print("%s:%s  " % (codon,codon_to_amino(codon)), end=" ")
            print(' ')
        print(' ')

    # DEGUG: test direct and inverse DNA/RNA lookup in conversion table
    # print("tau  ->  %s" % codon_to_amino("tau",True))
    # print("Ser/S  ->  %s" % str(amino_to_codon("Ser/S",True)))

    n = len(codon_amino)
    # print('size = %d' % n)
    
    amino_err = [ 0, 0, 0, 0 ]      # 'error' counter for 0,1,2,3 changes in codons
    amino_ok = [ 0, 0, 0, 0 ]       # 'correct' counter for 0,1,2,3 changes in codons
    # step-2: generate all codons, assume as mutations and compare (error counts)
    for a in ['T','C','A','G']:
        for c in ['T','C','A','G']:
            for b in ['T','C','A','G']:
                for codon in codon_amino.keys():        # compare current codon with all valid codons
                    newcodon = a+b+c
                    err_count = count_errors(codon,newcodon)    # assume as mutation, count mutations in codon
                    if codon_to_amino(newcodon) != codon_to_amino(codon):   # check conversions to proteins
                        amino_err[err_count] = amino_err[err_count] + 1     # update 'errors' counter if different
                    else:
                        amino_ok[err_count] = amino_ok[err_count] + 1       # update 'correct' counter if same

    # step-3: display all errors/correct counters and statistics
    print("total pairs = %d  ->  total errors = %d" % (n*n, sum(amino_err[1:4])))
    print("correct count: %s  ->  sum: %d (%.2f%%)" % (str(amino_ok), sum(amino_ok), sum(amino_ok)/(n*n)*100) )
    print("errors count: %s  ->  sum: %d  (%.2f%%)" % (str(amino_err), sum(amino_err), sum(amino_err)/(n*n)*100) )
    print("baseline correct: %d  ->  augmented correct: %d (+%.2f%%)" % (amino_ok[0], sum(amino_ok), (sum(amino_ok)/amino_ok[0]-1)*100) )

    # step-4: estimate efficiency (no-error rate) in protein decoding for 0,1,2,3 errors in codon
    ratio_ok = [ amino_ok[0]/(amino_ok[0]+amino_err[0]), amino_ok[1]/(amino_ok[1]+amino_err[1]),
                 amino_ok[2]/(amino_ok[2]+amino_err[2]), amino_ok[3]/(amino_ok[3]+amino_err[3]) ]
    print("efficiency (err=0,1,2,3): [%.3f, %.3f, %.3f, %.3f]" % (ratio_ok[0], ratio_ok[1], ratio_ok[2], ratio_ok[3]) )
    
    # step-5: estimate efficiency (no-error rate) in protein decoding for 'Perr' probability of base mutation in codon
    Perr = 0.10             # baseline single-base mutation probability
    P1 = Perr               # mutation probability of 1 base in codon
    P2 = Perr*Perr          # mutation probability of 2 bases in codon
    P3 = Perr*Perr*Perr     # mutation probability of 3 bases in codon
    P0 = 1-P1-P2-P3         # no-mutation probability in codon
    avg_ok = P0*ratio_ok[0] + P1*ratio_ok[1] + P2*ratio_ok[2] + P3*ratio_ok[3]      # expectancy (w.avg) of correct codon decoding
    print("efficiency (Perr=%.2f): [%.3f, %.3f, %.3f, %.3f]  ->  %.3f" % (Perr, P0*ratio_ok[0], 
                        P1*ratio_ok[1], P2*ratio_ok[2], P3*ratio_ok[3], avg_ok) )
