/* ping.c */
#include "ping.h"

int16 checksum(int8 *pkt, int16 size) {
    int16 *p;
    int32 acc, b;
    int16 carry;
    int16 n;
    int16 sum;

    acc = 0;
    for (n=size, p = (int16 *)pkt; n; n -= 2, p++) {
        b = *p;
        acc += b;
    }
    carry = ((acc & 0xffff0000)>>16);
    sum = (acc & 0x0000ffff);

    return ~(sum+carry);
}
int8 *eval_icmp(icmp *pkt) {
    int8 *p, *ret;
    int16 size;
    struct s_rawicmp rawpkt;
    struct s_rawicmp *rawptr;
    int16 check;

    if (!pkt || !pkt->data)
        return $1 0;
    
    switch (pkt->kind) {
        case echo:
            rawpkt.type = 8;
            rawpkt.code = 0;

            break;
        
        case echoreply:
            rawpkt.type = 0;
            rawpkt.code = 0;

            break;
        
        default:
            return $1 0;
            break;
    }

    rawpkt.checksum = 0;
    size = sizeof(struct s_rawicmp) + pkt->size;
    if (size%2)
        size++;

    p = $1 malloc($i size);
    ret = p;
    assert(p);
    zero($1 p, size);

    copy(p, $1 &rawpkt, sizeof(struct s_rawicmp));
    p += sizeof(struct s_rawicmp);
    copy(p, pkt->data, pkt->size);

    check = checksum(ret, size);
    rawptr = (struct s_rawicmp *)ret;
    rawptr->checksum = check;

    return ret;
}

icmp* make_icmp(type kind, const int8* data, int16 size){
	int16 n;
	icmp* p;

	if(!data || (size<=0))
		return (icmp*)0;

	n=sizeof(struct s_icmp)+ size;
	p=(icmp*) malloc($i n);
	assert(p);

	zero($1 p, n);
	p->kind = kind;
	p->size = size;
	p->data = data;

	return p;
}

void showicmp(icmp*packet){
	if(!packet)
		return;
	printf("kind :\t %s\nsize:\t %d\npayload: \n", ((packet->kind == echo) ? "echo" : "echoreply"), $i packet->size);

	if(packet->data){
		printhex(packet->data, packet->size,0);
	}
	printf("\n");
}

int main(int argc, char*argv[]){
    	int8 *str;
    	int8 *raw;
    	icmp *pkt;
    	int16 size;

    	str = $1 malloc(6);
    	assert(str);
    	zero(str, $2 6);
    	strncpy($c str, "Hello", 5);

    	pkt = make_icmp(echo, str, $2 5);
    	assert(pkt);
    	showicmp(pkt);

    	raw = eval_icmp(pkt);
    	assert(raw);
    	size = sizeof(struct s_rawicmp) + pkt->size;

    	printhex(raw, size, 0);
    	free(pkt->data);
        free(pkt);

	return 0;

}
