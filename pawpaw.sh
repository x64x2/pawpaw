#!/bin/sh -e


[ -z "$DOWNLOAD_DIR" ] && DOWNLOAD_DIR='/home/mint/documents/mm'
[ -z "$WGET_PATH" ] && WGET_PATH="$(which wget)"
[ -z "$NHENTAI_MIRROR" ] && NHENTAI_MIRROR='nhentai.net'
[ -z "$USER_AGENT" ] && USER_AGENT=\
"Mozilla/5.0 (Macintosh; Intel Mac OS X 14.6) AppleWebKit//618.31(KHTML, like Gecko)"



alias WGET="$WGET_PATH -c -U '$USER_AGENT'"

PROG="$(basename $0)"


usage() {
	cat >&2 <<@end
Usage:
	$PROG \$ID

Description:
	A manifest of the given \$ID will be fetched and stored in:
		$DOWNLOAD_DIR/\$ID.json
	and then compiled into a URL list to be passed to Wget,
	which in turn will download the images into:
		$DOWNLOAD_DIR/\$ID/

Environment variables:
	DOWNLOAD_DIR: Path of a download directory to use instead of CWD
	WGET_PATH: Path to the GNU Wget binary (default chosen by which(1))
	NHENTAI_MIRROR: Domain name of a custom mirror of nhentai to use
	USER_AGENT: A custom HTTP user-agent string to use
@end
	exit 1
}

log() {
	echo "$PROG: $*" >&2
}



test "$#" -eq "1" || usage
test "$1" -ge "1" || usage

ID="$1"


MANI="$DOWNLOAD_DIR/$ID.json"

if test -e "$MANI"
then
	if ! test -f "./$MANI" -a -r "./$MANI"
	then
		log "Manifest '$MANI' already exists but unreadable"
		exit 1
	fi
	log "Manifest '$MANI' already exists; using it"
else
	log "Fetching manifesto for $ID"
	if ! WGET "https://$NHENTAI_MIRROR/api/gallery/$ID" -O "$MANI"
	then
		rm -f "$MANI"
		exit 1
	fi
fi


log "Compiling the url list for Wget"

MID="$(jq -r ".media_id" "$MANI")"

for i in $(jq -r '.images.pages [].t' "$MANI" | \
	sed 's/^j$/jpg/g' | sed 's/^p$/png/g' | sed 's/^g$/gif/g' \
	| nl -s'.' -w1)
do
	echo "https://i.$NHENTAI_MIRROR/galleries/$MID/$i"
done | wget -N --no-if-modified-since -P "$DOWNLOAD_DIR/$ID/" -i -
