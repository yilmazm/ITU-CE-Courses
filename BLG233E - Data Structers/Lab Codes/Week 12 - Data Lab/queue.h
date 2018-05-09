/* @Author
 * Muhammed YILMAZ
 * yilmazmu15@gmail.com
 * 2017 Spring
 */

#ifndef QUEUE_H
#define QUEUE_H

struct qNode
{
	int deger;
	qNode *prev;
};


struct queue
{
	qNode *tepeEleman;
	qNode *tailEleman;
	void create();
	void push(int tempDeger);
	bool pull();
	void show();
	qNode top();
};

#endif