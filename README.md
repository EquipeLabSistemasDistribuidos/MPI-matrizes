# MPI matrizes
## Dependências no Linux (ou WSL no Windows) do RMI

```
sudo apt install openssh-client
```
```
sudo apt install openssh-server
```

```
sudo apt install libopenmpi-dev
```

```
sudo apt install libopenmpi3
```


## Execução do RMI
```
mpicc matriz-mpi.c -o saida
```

```
mpirun -n 4 ./saida
```

## Dependências no Linux (ou WSL no Windows) para COMPILAR CÓDIGO EM C (não solicitado pelo Professor)
```
sudo apt install gcc
```

## Execução da matriz normal pelo GCC (não solicitado pelo Professor)
```
gcc matriz.c -o saida
```
```
./saida
```

#LINKS
```
https://sites.google.com/a/liesenberg.biz/cjogos/home/materiais-de-apoio/topicos-relativos-a-c/matrizes/soma-de-matrizes
```
