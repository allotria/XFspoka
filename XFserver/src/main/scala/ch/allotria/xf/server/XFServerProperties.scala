package ch.allotria.xf
package server

import scala.collection.JavaConversions.propertiesAsScalaMap
import java.util.Properties
import java.io.FileReader

object XFServerProperties {
  private val propertyFile: String = "./XFserver.properties"

  private val jProps = new Properties()
  jProps.load(new FileReader(propertyFile))
  private val props: scala.collection.Map[String, String] = jProps

  def getValue(name: String): Option[String] = props get name
}
