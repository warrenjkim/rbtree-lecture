# Red Black Tree Lecture Notes

These are the lecture notes I used along with a code demo of insertion.

## NOTE FOR CS32 STUDENTS

Note that this implementation inserts equality to the left subtree. This may or may not be consistent with what
you have learned in class. **Please use the algorithm provided in class, not the one that is implemented in the
code demonstration.**

## Lecture Notes

The lecture in a pdf format written in $\LaTeX$. For brevity, only insertion was covered.

## Running the Code Demo

To run the code demo, first clone the repository:

```bash
git clone https://github.com/warrenjkim/rbtree-lecture
```

Then `cd` into the directory:

```bash
cd rbtree-lecture/code
```

Once inside the directory, run:

```bash
make
```

to make the executable. By default, the output is set to `./rbt`. You can change the 
name of the executable in the `Makefile`. Now run the program:

```bash
./rbt
```

**Note:** Only insertion is implemented, since deletion was outside the scope of the lecture.

## Documentation (Doxygen)

To view the auto-generated documentation, the HTML can be found [here](https://github.com/warrenjkim/rbtree-lecture/tree/master/code/html/index.html), 
and the corresponding $\LaTeX$ PDF [here](https://github.com/warrenjkim/rbtree-lecture/tree/master/code/latex/refman.pdf).
