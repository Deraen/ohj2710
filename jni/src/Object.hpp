/*
 * Object.h
 *
 *  Created on: Sep 24, 2012
 *      Author: juho
 */

#ifndef OBJECT_H_
#define OBJECT_H_

class Object
{
public:
	/*
	 * Object constructors DO NOTHING.
	 * Reset should always be called after creating new Object.
	 */
	Object();
	virtual ~Object();

	/*
	 * Objects can ask for their own id.
	 */
	unsigned int getId() const;

	/*
	 * Manager can se objects id.
	 */
	void setId(const unsigned int i);

private:
	unsigned int id_;
};

#endif /* OBJECT_H_ */
