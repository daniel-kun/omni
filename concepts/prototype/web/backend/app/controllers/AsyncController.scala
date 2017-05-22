package controllers

import akka.actor.ActorSystem
import javax.inject._
import play.api._
import scala.concurrent.{ExecutionContext, Future, Promise}
import scala.concurrent.duration._

import sangria.schema._

case class IntLiteral (id: String, value: Int)

/**
 * This controller creates an `Action` that demonstrates how to write
 * simple asynchronous code in a controller. It uses a timer to
 * asynchronously delay sending a response for 1 second.
 *
 * @param actorSystem We need the `ActorSystem`'s `Scheduler` to
 * run code after a delay.
 * @param exec We need an `ExecutionContext` to execute our
 * asynchronous code.
 */
@Singleton
class AsyncController @Inject() (actorSystem: ActorSystem)(implicit exec: ExecutionContext) extends play.api.mvc.Controller {

  /**
   * Create an Action that returns a plain text message after a delay
   * of 1 second.
   *
   * The configuration in the `routes` file means that this method
   * will be called when the application receives a `GET` request with
   * a path of `/message`.
   */
  def message = play.api.mvc.Action.async {
    getFutureMessage(1.second).map { msg => Ok(msg) }
  }

  def foobar = play.api.mvc.Action {
    Ok("Hello, World!")
  }

  /*
  val IntLiteralType = ObjectType (
    "int literal",
    "An int literal expression",
    fields [Units, IntLiteral](
      Field("id", StringType, resolve = _.value.id),
      Field("value", IntType, resolve = _.value.value)))
  */

  private def getFutureMessage(delayTime: FiniteDuration): Future[String] = {
    val promise: Promise[String] = Promise[String]()
    actorSystem.scheduler.scheduleOnce(delayTime) { promise.success("Hi!") }
    promise.future
  }

}
