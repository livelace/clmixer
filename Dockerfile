FROM            harbor-core.k8s-2.livelace.ru/dev/clmixer:latest

ENV             CLMIXER_BIN="/usr/local/bin/clmixer"

# copy application.
COPY            "work/clmixer" "$CLMIXER_BIN"

USER            "user"

WORKDIR         "/home/user"

CMD             ["/usr/local/bin/clmixer"]
