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
	 * Should reset object to "empty" state so that object can be used again.
	 *
	 * In addition to this every object should have initialize-method which will be used
	 * like constructor.
	 * eg. Player::initialize(const string& name)
	 *
	 * Reset doesn't have to change values which will be set by intialize (eg. Players name)
	 * but it should release other objects which it owns (eg. Players planet).
	 */
	void reset();
	virtual void reset_inner() = 0;

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
