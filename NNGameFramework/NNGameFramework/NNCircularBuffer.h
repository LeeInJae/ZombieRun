
/**
 * NNCircularBuffer.h
 * 작성자: 이선협
 * 작성일: 2013. 11. 12
 * 마지막으로 수정한 사람: 이선협
 * 수정일: 2013. 12. 04
 */

#pragma once

class NNCircularBuffer
{
public:
	friend class NNNetworkSystem;

	NNCircularBuffer(size_t capacity) ;
	~NNCircularBuffer() ;

public:
	size_t GetCurrentSize() const
	{ 
		return mCurrentSize ; 
	}

	size_t GetCapacity() const
	{ 
		return mCapacity ;
	}

	bool Write(const char* data, size_t bytes) ;

	bool Read(char* data, size_t bytes) ;

	/// 데이터 훔쳐보기 (제거하지 않고)
	void Peek(char* data) ;
	bool Peek(char* data, size_t bytes) ;

	/// 데이터 제거
	bool Consume(size_t bytes) ;

private:
	size_t mBeginIndex ;
	size_t mEndIndex ;
	size_t mCurrentSize ;
	size_t mCapacity ;

	char* mData ;
};
