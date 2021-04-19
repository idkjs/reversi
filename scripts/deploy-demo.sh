  !#/bin/sh
  cd build && \
  git init && \
  git add . && \
  git commit -m "Update demo" && \
  git remote add origin git@github.com:idkjs/reversi.git && \
  git push --force origin main:gh-pages
  rm -Rf build
