#!/bin/bash

MOL=$1
PDB_FRAMES_FOLDER=$2

pdb2gmx -f ${MOL}.pdb -o ${MOL}.gro -p ${MOL}.top << KOKO
1
1
KOKO

#editconf -f ${MOL}.gro -o ${MOL}.gro -d 0.5 
#genbox -cp ${MOL}.gro -cs -o ${MOL}_b4em.gro -p ${MOL}.top

cat > em.mdp << _EOF_
title               =  ${MOL}
cpp                 =  /usr/bin/cpp
define              =  -DFLEX_SPC
constraints         =  none
integrator          =  steep
nsteps              =  100
nstlist             =  10
ns_type             =  grid
rlist               =  1.0
rcoulomb            =  1.0
rvdw                =  1.0
;
;       Energy minimizing stuff
;
emtol               =  1000.0
emstep              =  0.01
_EOF_


grompp -f em -c ${MOL} -p ${MOL} -o ${MOL}_em
mdrun -nice 4 -s ${MOL}_em -o ${MOL}_em -c ${MOL}_b4md

#grompp -f em -c ${MOL}_b4em -p ${MOL} -o ${MOL}_em
#mdrun -nice 4 -s ${MOL}_em -o ${MOL}_em -c ${MOL}_b4md

cat > md.mdp << _EOF_
title               =  ${MOL} MD
cpp                 =  /usr/bin/cpp
constraints         =  all-bonds
integrator          =  md
dt                  =  0.002	; ps !
nsteps              =  5000	; total 10.0 ps.
nstcomm             =  1
nstxout             =  50
nstvout             =  0
nstfout             =  0
nstlist             =  10
ns_type             =  grid
rlist               =  1.0
rcoulomb            =  1.0
rvdw                =  1.0
; Berendsen temperature coupling is on in two groups
Tcoupl              =  berendsen
tau_t               =  0.1	     0.1
tc-grps		    =  protein	     sol
ref_t               =  300	     300
; Pressure coupling is not on
Pcoupl              =  no
tau_p               =  0.5
compressibility     =  4.5e-5
ref_p               =  1.0
; Generate velocites is on at 300 K.
gen_vel             =  yes
gen_temp            =  300.0
gen_seed            =  173529
_EOF_

grompp -f md -c ${MOL}_b4md  -p ${MOL} -o ${MOL}_md 
mdrun -nice 4 -s ${MOL}_md -o ${MOL}_md -c ${MOL}_after_md

#create pdbs

mkdir -p ${PDB_FRAMES_FOLDER}

cd ${PDB_FRAMES_FOLDER}

echo "0" | trjconv -f ../${MOL}_md.trr -s ../${MOL}_md.tpr -o ${MOL}_ind.pdb -sep

