#Parallel Statistics using named pipes

Sorry readme is in Greek.

MAIN_CHECK_ARGS: Ελέγχει τα arguments από το command line και παίρνει το βάθος και το όνομα του αρχείου.
MAIN_GET_FILE_RECORD_NUM: Ανοίγει και διαβάζει όλο το αρχείο για να βρει τον αριθμό των εγγραφών.
MAIN_PROMPT: Είναι η συνάρτηση που εμφανίζει το prompt και ελέγχει τα commands. Καλεί τη START_SEARCH που κάνει το πρώτο fork.
START_SEARCH: Παίρνει τα στοιχεία που χρειάζονται για την αναζήτηση, και κάνει fork το βασικό κόμβο/ main_node με τα στοιχεία που έχει ως ορίσματά του. 

main_node: Ξεχωριστή διεργασία. Υπολογίζει πόσες εγγραφές θα ελέγξει κάθε searcher. Το αποθηκεύει σδτο block. 
Φτιάχνει το βασικό pipe που την ενώνει με τον πρώτο merger. 
Κάνει fork τον πρώτο merger.
Διαβάζει το pipe και διαχωρίζει τα στατιστικά από τα records που έρχονται, γράφοντας τα records στο tmp αρχείο.. 
Όταν επιστρέψει και τερματίσει ο βασικός merger, κάνει άλλο ένα fork καλώντας τη sort η οποία θα κάνει αριθμητικό sort στο tmp αρχείο και θα βγάλει το αποτέλεσμα στο _sorted αρχείο. Όταν κάνει τελειώσει και η sort, ανοίγω το αρχείο sorted και διαβάζω στην οθόνη. 


merger: υπολογίζει το depth κάθε επιπέδου και κάθε ένας από τους merger κανει και 2 fork.
φτιάχνει και τα απαραίτητα pipes για να επικοινωνεί. Αν το βάθος (δηλαδή ύψος εδώ) φτάσει 0 κάνει fork 2 searcher.
Αλλιώς κάνει fork mergers. 
Ο πατέρας merger απλά διαβάζει το pipe και μεταφέρει προς τα επάνω. 
Ένα σημείο που δυσκόλεψε αρκετά ήταν το πώς θα δίνω τα σωστά περιθώρια στους searchers για να ψάχνουν στο αρχείο. 
Χρησιμοποίησα bitwise operators για να υπολογίσω τον αριθμό του κάθε searcher στο δυαδικό και κατεπέκταση είχα τη δεκαδική του μορφή έτοιμη. 
searcher:
Έτσι κάθε searcher με βάση τον αύξοντα αριθμό του και γνωρίζοντας ότι ο κάθε searcher θα ψάχνει σε block αριθμό εγγραφών, γνωρίζει την αρχή και το τέλος της αναζήτησης μέσα στο αρχείο. Το υπολογίζει για την ακρίβεια. Άρα ξεκινάει την αναζήτηση και κοιτάζοντας τον τύπο του πεδίου, οργανώνει τις μεταβλητές που θα σταλλούν στην εκάστοτε compare, άλλη για int και άλλη για string.
Υπολογίζει και το χρόνο και τα στέλνει πίσω μέσω pipe. 



COMPARE: Επιστρέφει 1 αν για τα πεδία που καλλείται ισχύει ο τελεστής που της δίνεται. Για strings.

COMPARENUM: Αντίστοιχα για αριθμούς. 



