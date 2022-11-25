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
## Dependências no Linux (ou WSL no Windows) para COMPILAR CÓDIGO EM C 

## Execução do RMI
```
mpicc matriz-mpi -o saida
```

```
mpirun -n 4 ./saida
```

## Execução da matriz normal pelo GCC (não é pedido para a tarefa do Professor)
```
sudo apt install gcc
```

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
