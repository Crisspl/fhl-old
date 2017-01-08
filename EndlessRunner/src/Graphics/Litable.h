#ifndef FHL_LITABLE_H
#define FHL_LITABLE_H

#include "Light.h"

#include <list>
#include <vector>
#include <type_traits>

namespace fhl
{

	 class Litable
	 {
	 public:
		  virtual ~Litable() = default;

		  void addLight(const Light & _light)
		  {
				m_lights.push_back(_light);
		  }
		  void addLights(const std::vector<Light> & _lights)
		  {
				m_lights.insert(m_lights.cbegin(), _lights.cbegin(), _lights.cend());
		  }

		  void setLight(const Light & _light)
		  {
				m_lights.clear();
				addLight(_light);
		  }
		  void setLights(const std::vector<Light> & _lights)
		  {
				m_lights.clear();
				addLights(_lights);
		  }
		  template<typename _It>
		  void setLights(_It _begin, const _It _end);

		  size_t getLightsCount() const { return m_lights.size(); }
		  const std::list<Light> & getLights() const { return m_lights; }

	 protected:
		  std::list<Light> m_lights;
	 };

	 template<typename _It>
	 void Litable::setLights(_It _begin, const _It _end)
	 {
		  static_assert(std::is_same<typename _It::value_type, Light>::value,
				"_begin and _end must be iterators of containers of fhl::Light objects");

		  while (_begin != _end)
				setLight(*(_begin++));
	 }

}

#endif // FHL_LITABLE_H
