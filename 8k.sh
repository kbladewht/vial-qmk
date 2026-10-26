


qmk compile -j 4 -kb keychron/c2_pro_8k/ansi -km vial

# make keychron/c2_pro_8k/ansi:vial

#qmk compile -j 4 -kb at8k_test -km via
 qfroot=keychron
 qfkeymap=vial
 pconfig1=c2_pro_8k
qf_path=$(pwd)
 pconfig3=ansi
echo "${GREEN} building ${qfroot}/${pconfig1}:via ...$END\n"


RED='\e[1;31m'
GREEN='\e[1;32m'
YELLOW='\033[1;33m'
BLUE='\E[1;34m'
PINK='\E[1;35m'  # 粉红
END='\033[0m'  # 清除颜色


polling_check(){
count=0
while [ ! -f E:/INFO_UF2.TXT ] && [ ! -f F:/INFO_UF2.TXT ]; do
    sleep 2
    count=$((count + 1))

    if [ $count -gt 50 ]; then
        echo "\nBeyong attempt, break current build..."
        break
    fi

    if (( count == 1 )); then
        echo "E:/flash.uf2 can't find, polling check...every 2 seconds"
        echo -n "Detecting..."
        continue
    fi

    echo -n "."

done
}

# qmk compile -j 11 -kb 8k_bl -km via
    echo "${qf_path}/.build/keychron_c2_pro_8k_ansi_vial.uf2 to    E:/flash.uf2"
    polling_check
    cp ${qf_path}/.build/keychron_c2_pro_8k_ansi_vial.uf2 E:/flash.uf2


