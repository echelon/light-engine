#ifndef LE_PIPELINE_FAUXMATSTACK
#define LE_PIPELINE_FAUXMATSTACK

#include <vector>

/**
 * This is just temporary until I write a matrix stack.
 * It should have a fairly similar API allowing me to introduce the 
 * streamer drawing API.
 */
namespace LE {

  struct Translation {
	float x;
	float y;
	Translation(): x(0.0f), y(0.0f) {};
	Translation(float x_, float y_) : x(x_), y(y_) {};
  };

  class FauxMatStack {
	protected:
	  std::vector<Translation> translationStack;

	public: 
	  //FauxMatStack();
	  //~FauxMatStack();
	  
	  void push(const Translation t);
	  void push(const float x, const float y);

	  void pop();

	  void clear() { translationStack.clear(); };
  };
}

#endif
