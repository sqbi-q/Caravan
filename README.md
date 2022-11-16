# Caravan - Cool ASCII Art Editor

Caravan is multi-layered ASCII/Unicode-art editor, which goal is implementation of *cool* features and further improvement of *predecessor's* functionality.

This project is fork of [Aewan](http://aewan.sourceforge.net) - created by Bruno Takahashi C. de Oliveira and licensed under the GNU General Public License.

# Installation

After cloning this repository, you compile and install it the same way as provided by [Aewan's README](./README):

```
$ cd Caravan
$ ./configure
$ make
$ su -c 'make install'
```

# License

Same license as for Aewan is used, that being [GNU General Public License v2.0](./COPYING).

---

## What is Aewan?

`Aewan is a multi-layered ascii-art/animation editor that produces
both stand-alone cat-able art files and an easy-to-parse format for integration
in your terminal applications. It is primarily designed for Linux, although it
currently also compiles under FreeBSD and possibly other *NIX systems.`

More details available in [Aewan's README](./README) and its home page: http://aewan.sourceforge.net

## Contribution for Aewan
List present in Aewan's README:
  - Bruno T. C. de Oliveira (brunotc@gmail.com)
  - Peep Pullerits (http://solicit.estprog.ee; solicit@estprog.ee)
  - Praveen Kurup <praveen_kurup@jasubhai.com>
  - Gerfried Fuchs <alfie@ist.org>

## What Caravan changed? What are those *cool* features?
  - Extended editor's character size to 4 bytes, allowing creating, storing and displaying of Unicode art (e.g. symbols such as `´`,  `‾`, `¡` and `·`).
