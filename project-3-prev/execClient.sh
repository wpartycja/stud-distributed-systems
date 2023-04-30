# Lanzamiento de un cliente que reinicia el servidor, y tres que agregan sus propias
# claves independientes, copian estas a una común, e imprimen sus valores

#!/bin/bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./
export IP_TUPLAS=localhost

./client localhost
