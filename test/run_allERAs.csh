#!/bin/csh -f

foreach era ( C D E-v1 E-v2 F )
    echo Processing ERA 2017$era
    cp ROOTFILELIST/rootFileList_2017$era.txt rootFileList.txt
    ./naf_all.csh SimpleMssmHbbmuAnalysis template.cfg rootFileList.txt 3
    cp Merge_Histo/histograms.root ROOTFILES/histograms_2017$era.root
    cp -R Merge_Histo STORE/2017$era
    echo '================================================'
end

